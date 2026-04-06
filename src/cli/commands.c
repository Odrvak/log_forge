/*
 * commands.c — Top-level command dispatcher.
 *
 * Wires together the file reader, statistics accumulator, line filters,
 * and output functions according to the options stored in config_t.
 */

#include "commands.h"
#include "../core/file_reader.h"
#include "../analysis/filter.h"
#include "../analysis/stats.h"
#include "../output/print.h"

#include <stdio.h>

/*
 * Internal state shared between commands_run() and the per-line callback.
 */
typedef struct {
    const config_t *cfg;
    log_stats_t     stats;
    int             print_lines;
} run_context_t;

/*
 * Called once for every line read from the file.
 *
 * Updates the running statistics unconditionally, then prints the line if
 * it passes the active filter. Returns 1 to continue reading.
 */
static int on_line(const log_line_t *line, void *userdata)
{
    run_context_t *ctx = (run_context_t *)userdata;

    stats_update(&ctx->stats, line);

    if (ctx->print_lines) {
        int show = 0;

        if (ctx->cfg->show_errors_only) {
            show = filter_is_error(line);
        } else if (ctx->cfg->filter_keyword) {
            show = filter_match(line, ctx->cfg->filter_keyword);
        } else {
            show = 1;
        }

        if (show) {
            print_line(line);
        }
    }

    return 1;
}

/*
 * Runs the command described by 'cfg'.
 *
 * Streams the input file through on_line(), then prints the statistics
 * table if --stats was requested. When --stats is the only active option,
 * per-line output is suppressed and only counts are collected.
 * Returns 0 on success, 1 on error.
 */
int commands_run(const config_t *cfg)
{
    run_context_t ctx;
    ctx.cfg = cfg;
    stats_reset(&ctx.stats);

    // Suppress line-by-line output when the user only wants the summary.
    // Any filter option re-enables printing so the user can see what matched.
    if (cfg->show_stats && !cfg->filter_keyword && !cfg->show_errors_only) {
        ctx.print_lines = 0;
    } else {
        ctx.print_lines = 1;
    }

    if (file_reader_process(cfg->filename, on_line, &ctx) != 0) {
        fprintf(stderr, "Error: Could not open '%s'. Check that the file exists and is readable.\n",
                cfg->filename);
        return 1;
    }

    if (cfg->show_stats) {
        print_stats(&ctx.stats, cfg->filename);
    }

    return 0;
}

/*
 * print.c — Terminal output formatting for LogForge.
 *
 * All output directed to stdout passes through these functions, keeping
 * the presentation layer separate from the analysis and filtering logic.
 */

#include "print.h"
#include "../core/parser.h"

#include <stdio.h>

#define SEPARATOR "------------------------------------------------------------"

/*
 * Prints a horizontal separator line to stdout.
 */
void print_separator(void)
{
    puts(SEPARATOR);
}

/*
 * Prints a single log line with its line number and detected severity label.
 * Output format:  [line_num] [LEVEL] raw text
 */
void print_line(const log_line_t *line)
{
    printf("[%6zu] [%s] %s\n",
           line->line_num,
           parser_level_str(line->level),
           line->raw);
}

/*
 * Prints a formatted statistics table for the processed file.
 * Shows the total line count followed by a per-level breakdown.
 */
void print_stats(const log_stats_t *s, const char *filename)
{
    printf("\n");
    print_separator();
    printf("  LogForge Statistics -- %s\n", filename);
    print_separator();
    printf("  %-12s : %zu\n", "Total Lines", s->total);
    printf("  %-12s : %zu\n", "Errors",      s->errors);
    printf("  %-12s : %zu\n", "Warnings",    s->warnings);
    printf("  %-12s : %zu\n", "Info",        s->infos);
    printf("  %-12s : %zu\n", "Debug",       s->debugs);
    printf("  %-12s : %zu\n", "Unknown",     s->unknowns);
    print_separator();
    printf("\n");
}

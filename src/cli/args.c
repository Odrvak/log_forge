/*
 * args.c — Command-line argument parser.
 *
 * Converts argc/argv into a config_t struct. Unknown flags and missing
 * required values are reported to stderr with a descriptive message.
 */

#include "args.h"

#include <stdio.h>
#include <string.h>

/*
 * Prints the version string to stdout.
 */
void args_print_version(void)
{
    printf("LogForge v%s\n", LOGFORGE_VERSION);
}

/*
 * Prints usage instructions and a list of available options to stdout.
 */
void args_print_usage(const char *prog)
{
    printf("LogForge v%s -- Embedded Log Analyzer\n\n", LOGFORGE_VERSION);
    printf("Usage:\n");
    printf("  %s <file> [options]\n\n", prog);
    printf("Options:\n");
    printf("  --filter <keyword>   Show only lines containing the given keyword.\n");
    printf("  --stats              Print a summary of log level counts.\n");
    printf("  --errors             Show only lines with ERROR severity.\n");
    printf("  --version            Show the version number and exit.\n");
    printf("  --help               Show this help message and exit.\n\n");
    printf("Examples:\n");
    printf("  %s app.log --filter ERROR\n", prog);
    printf("  %s app.log --stats\n", prog);
    printf("  %s app.log --errors\n", prog);
}

/*
 * Parses 'argc' / 'argv' into 'cfg'.
 *
 * The first non-flag token is treated as the input filename. Flags may
 * appear in any order. Returns 0 on success, -1 if an argument is
 * invalid or a required value is absent.
 */
int args_parse(int argc, char *argv[], config_t *cfg)
{
    cfg->filename         = NULL;
    cfg->filter_keyword   = NULL;
    cfg->show_stats       = 0;
    cfg->show_errors_only = 0;
    cfg->show_help        = 0;
    cfg->show_version     = 0;

    if (argc < 2) {
        return -1;
    }

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--help") == 0 || strcmp(argv[i], "-h") == 0) {
            cfg->show_help = 1;
            return 0;
        } else if (strcmp(argv[i], "--version") == 0 || strcmp(argv[i], "-v") == 0) {
            cfg->show_version = 1;
            return 0;
        } else if (strcmp(argv[i], "--stats") == 0) {
            cfg->show_stats = 1;
        } else if (strcmp(argv[i], "--errors") == 0) {
            cfg->show_errors_only = 1;
        } else if (strcmp(argv[i], "--filter") == 0) {
            if (i + 1 >= argc) {
                fprintf(stderr, "Error: --filter requires a keyword argument.\n");
                return -1;
            }
            cfg->filter_keyword = argv[++i];
        } else if (argv[i][0] == '-') {
            fprintf(stderr, "Error: Unknown option '%s'. Run with --help to see available options.\n",
                    argv[i]);
            return -1;
        } else {
            if (cfg->filename) {
                fprintf(stderr, "Error: Only one input file is supported per invocation.\n");
                return -1;
            }
            cfg->filename = argv[i];
        }
    }

    if (!cfg->filename) {
        fprintf(stderr, "Error: No input file specified.\n");
        return -1;
    }

    return 0;
}

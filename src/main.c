/*
 * main.c — Program entry point for LogForge.
 *
 * Parses command-line arguments into a config_t struct, handles the
 * immediate flags (--help, --version), then dispatches to the
 * appropriate command handler.
 */

#include "logforge.h"
#include "cli/args.h"
#include "cli/commands.h"

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    config_t cfg;

    if (args_parse(argc, argv, &cfg) != 0) {
        args_print_usage(argv[0]);
        return EXIT_FAILURE;
    }

    if (cfg.show_version) {
        args_print_version();
        return EXIT_SUCCESS;
    }

    if (cfg.show_help) {
        args_print_usage(argv[0]);
        return EXIT_SUCCESS;
    }

    return commands_run(&cfg) == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}

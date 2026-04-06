/*
 * args.h — Interface for command-line argument parsing.
 */

#ifndef ARGS_H
#define ARGS_H

#include "../logforge.h"

/*
 * Fills 'cfg' from 'argc' and 'argv'.
 * Returns 0 on success, -1 if an argument is invalid or a required
 * value is missing.
 */
int args_parse(int argc, char *argv[], config_t *cfg);

/*
 * Prints usage instructions and a list of available options to stdout.
 */
void args_print_usage(const char *prog);

/*
 * Prints the version string to stdout.
 */
void args_print_version(void);

#endif /* ARGS_H */

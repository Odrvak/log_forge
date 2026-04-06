/*
 * print.h — Interface for terminal output formatting.
 */

#ifndef PRINT_H
#define PRINT_H

#include "../logforge.h"

/*
 * Prints a single log line with its line number and severity label.
 */
void print_line(const log_line_t *line);

/*
 * Prints a formatted statistics table for the processed file.
 */
void print_stats(const log_stats_t *s, const char *filename);

/*
 * Prints a horizontal separator line to stdout.
 */
void print_separator(void);

#endif /* PRINT_H */

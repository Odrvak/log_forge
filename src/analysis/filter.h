/*
 * filter.h — Interface for log line filtering.
 */

#ifndef FILTER_H
#define FILTER_H

#include "../logforge.h"

/*
 * Returns 1 if 'line' contains 'keyword' (case-insensitive).
 * Returns 1 for every line when 'keyword' is NULL (no filter applied).
 */
int filter_match(const log_line_t *line, const char *keyword);

/*
 * Returns 1 if 'line' has ERROR severity, 0 otherwise.
 */
int filter_is_error(const log_line_t *line);

#endif /* FILTER_H */

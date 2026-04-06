/*
 * stats.h — Interface for the log statistics accumulator.
 */

#ifndef STATS_H
#define STATS_H

#include "../logforge.h"

/*
 * Resets all counters in 's' to zero before a new file is processed.
 */
void stats_reset(log_stats_t *s);

/*
 * Increments the total line count and the counter for 'line's severity level.
 */
void stats_update(log_stats_t *s, const log_line_t *line);

#endif /* STATS_H */

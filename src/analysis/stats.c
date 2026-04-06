/*
 * stats.c — Log statistics accumulator.
 *
 * Tracks per-level line counts across all lines processed in a session.
 * The caller is responsible for calling stats_reset() before each file.
 */

#include "stats.h"

#include <string.h>

/*
 * Resets all counters in 's' to zero.
 */
void stats_reset(log_stats_t *s)
{
    memset(s, 0, sizeof(*s));
}

/*
 * Increments the total count and the per-level counter that matches 'line'.
 */
void stats_update(log_stats_t *s, const log_line_t *line)
{
    s->total++;

    switch (line->level) {
        case LEVEL_ERROR:   s->errors++;   break;
        case LEVEL_WARNING: s->warnings++; break;
        case LEVEL_INFO:    s->infos++;    break;
        case LEVEL_DEBUG:   s->debugs++;   break;
        default:            s->unknowns++; break;
    }
}

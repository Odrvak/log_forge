/*
 * parser.h — Interface for the log line parser.
 */

#ifndef PARSER_H
#define PARSER_H

#include "../logforge.h"

/*
 * Parses 'raw' into 'out', recording its line number and detected severity.
 * Recognized levels: ERROR, WARNING (or WARN), INFO, DEBUG.
 */
void parser_parse(const char *raw, size_t line_num, log_line_t *out);

/*
 * Returns a fixed-width label string for 'level', suitable for aligned output.
 */
const char *parser_level_str(log_level_t level);

#endif /* PARSER_H */

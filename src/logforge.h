/*
 * logforge.h — Shared type definitions for LogForge.
 *
 * This header is included by every module. It defines the core data
 * structures, constants, and enumerations used throughout the project.
 */

#ifndef LOGFORGE_H
#define LOGFORGE_H

#include <stddef.h>

#define LOGFORGE_VERSION  "1.0.0"
#define LINE_BUFFER_SIZE  4096
#define MAX_LEVEL_LEN     16
#define MAX_KEYWORD_LEN   256

/*
 * Log severity levels, ordered from least to most severe.
 * LEVEL_UNKNOWN is assigned when no recognized keyword is found in a line.
 */
typedef enum {
    LEVEL_UNKNOWN = 0,
    LEVEL_DEBUG,
    LEVEL_INFO,
    LEVEL_WARNING,
    LEVEL_ERROR
} log_level_t;

/*
 * Represents a single parsed line from a log file.
 * The raw field holds the original text of the line, stripped of newlines.
 */
typedef struct {
    size_t      line_num;
    log_level_t level;
    char        raw[LINE_BUFFER_SIZE];
} log_line_t;

/*
 * Accumulated per-level counts for all lines processed in a session.
 */
typedef struct {
    size_t total;
    size_t errors;
    size_t warnings;
    size_t infos;
    size_t debugs;
    size_t unknowns;
} log_stats_t;

/*
 * Holds the options parsed from the command line.
 * Only one input file is supported per invocation.
 */
typedef struct {
    const char *filename;
    const char *filter_keyword;
    int         show_stats;
    int         show_errors_only;
    int         show_help;
    int         show_version;
} config_t;

#endif /* LOGFORGE_H */

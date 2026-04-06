/*
 * filter.c — Log line filtering functions.
 *
 * Provides case-insensitive keyword matching and level-based filtering.
 * These functions are the sole decision point for whether a line is shown.
 */

#include "filter.h"

#include <string.h>
#include <ctype.h>

/*
 * Returns 1 if 'keyword' appears anywhere inside 'text', ignoring case.
 * An empty keyword matches every string unconditionally.
 */
static int contains_ignore_case(const char *text, const char *keyword)
{
    size_t text_len    = strlen(text);
    size_t keyword_len = strlen(keyword);

    if (keyword_len == 0) {
        return 1;
    }
    if (keyword_len > text_len) {
        return 0;
    }

    for (size_t i = 0; i <= text_len - keyword_len; i++) {
        size_t j;
        for (j = 0; j < keyword_len; j++) {
            if (tolower((unsigned char)text[i + j]) !=
                tolower((unsigned char)keyword[j])) {
                break;
            }
        }
        if (j == keyword_len) {
            return 1;
        }
    }
    return 0;
}

/*
 * Returns 1 if 'line' contains 'keyword' (case-insensitive).
 * If 'keyword' is NULL, every line is considered a match.
 */
int filter_match(const log_line_t *line, const char *keyword)
{
    if (!keyword) {
        return 1;
    }
    return contains_ignore_case(line->raw, keyword);
}

/*
 * Returns 1 if 'line' has ERROR severity, 0 otherwise.
 */
int filter_is_error(const log_line_t *line)
{
    return line->level == LEVEL_ERROR;
}

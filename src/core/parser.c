/*
 * parser.c — Log line parser.
 *
 * Detects the severity level of a log line and fills a log_line_t struct.
 * Level detection is performed in a single forward pass over the raw text,
 * using inline case folding instead of tolower() to avoid repeated
 * function-call overhead on every character.
 */

#include "parser.h"

#include <string.h>

/*
 * Scans 'str' for the first occurrence of a recognized log level keyword.
 * The comparison is case-insensitive and stops at the first match found.
 * Returns LEVEL_UNKNOWN if no known keyword appears in the string.
 */
static log_level_t detect_level(const char *str)
{
    for (; *str; str++) {
        switch (*str) {
            case 'E': case 'e':
                if ((str[1] == 'R' || str[1] == 'r') &&
                    (str[2] == 'R' || str[2] == 'r') &&
                    (str[3] == 'O' || str[3] == 'o') &&
                    (str[4] == 'R' || str[4] == 'r'))
                    return LEVEL_ERROR;
                break;

            case 'W': case 'w':
                if ((str[1] == 'A' || str[1] == 'a') &&
                    (str[2] == 'R' || str[2] == 'r') &&
                    (str[3] == 'N' || str[3] == 'n'))
                    return LEVEL_WARNING;
                break;

            case 'I': case 'i':
                if ((str[1] == 'N' || str[1] == 'n') &&
                    (str[2] == 'F' || str[2] == 'f') &&
                    (str[3] == 'O' || str[3] == 'o'))
                    return LEVEL_INFO;
                break;

            case 'D': case 'd':
                if ((str[1] == 'E' || str[1] == 'e') &&
                    (str[2] == 'B' || str[2] == 'b') &&
                    (str[3] == 'U' || str[3] == 'u') &&
                    (str[4] == 'G' || str[4] == 'g'))
                    return LEVEL_DEBUG;
                break;

            default:
                break;
        }
    }
    return LEVEL_UNKNOWN;
}

/*
 * Fills 'out' with the line number, detected severity, and a copy of 'raw'.
 * The raw text is copied as-is; only the level field is interpreted.
 */
void parser_parse(const char *raw, size_t line_num, log_line_t *out)
{
    out->line_num = line_num;
    out->level    = detect_level(raw);

    // Copy only the actual string content, not the full fixed-size buffer.
    size_t len = strlen(raw);
    if (len >= LINE_BUFFER_SIZE) {
        len = LINE_BUFFER_SIZE - 1;
    }
    memcpy(out->raw, raw, len);
    out->raw[len] = '\0';
}

/*
 * Returns a fixed-width, human-readable label for the given log level.
 * All labels are padded to the same width for aligned terminal output.
 */
const char *parser_level_str(log_level_t level)
{
    switch (level) {
        case LEVEL_ERROR:   return "ERROR";
        case LEVEL_WARNING: return "WARN ";
        case LEVEL_INFO:    return "INFO ";
        case LEVEL_DEBUG:   return "DEBUG";
        default:            return "     ";
    }
}

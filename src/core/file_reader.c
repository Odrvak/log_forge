/*
 * file_reader.c — Stream-based log file reader.
 *
 * Reads a text file line by line without loading the entire contents into
 * memory. Each line is parsed into a log_line_t struct and forwarded to a
 * user-supplied callback. Memory usage stays constant regardless of file size.
 */

#include "file_reader.h"
#include "parser.h"

#include <stdio.h>
#include <string.h>

/*
 * Opens the file at 'path' and processes it one line at a time.
 *
 * For each line read, the raw text is trimmed and parsed into a log_line_t,
 * then passed to 'callback' together with 'userdata'. If the callback
 * returns 0, reading stops immediately. Returns 0 on success, -1 if the
 * file cannot be opened.
 */
int file_reader_process(const char *path, line_callback_t callback, void *userdata)
{
    FILE       *fp;
    char        buf[LINE_BUFFER_SIZE];
    size_t      line_num = 0;
    log_line_t  line;

    fp = fopen(path, "r");
    if (!fp) {
        return -1;
    }

    while (fgets(buf, sizeof(buf), fp)) {
        line_num++;

        size_t len = strlen(buf);

        // Detect whether the line was too long to fit in the buffer.
        // fgets signals this by filling the buffer completely without
        // including a newline character at the end.
        int overflowed = (len == LINE_BUFFER_SIZE - 1) &&
                         (buf[len - 1] != '\n') && (buf[len - 1] != '\r');

        // Remove any trailing newline or carriage-return characters.
        while (len > 0 && (buf[len - 1] == '\n' || buf[len - 1] == '\r')) {
            buf[--len] = '\0';
        }

        // If the line was longer than the buffer, consume and discard the
        // remaining characters so the next iteration starts at the correct
        // position. The line is still processed using the first
        // LINE_BUFFER_SIZE - 1 characters, which contain the level keyword.
        if (overflowed) {
            int ch;
            while ((ch = fgetc(fp)) != EOF && ch != '\n') {
                ;
            }
        }

        parser_parse(buf, line_num, &line);

        if (callback(&line, userdata) == 0) {
            break;
        }
    }

    fclose(fp);
    return 0;
}

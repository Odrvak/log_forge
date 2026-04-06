/*
 * file_reader.h — Interface for the stream-based log file reader.
 */

#ifndef FILE_READER_H
#define FILE_READER_H

#include "../logforge.h"

/*
 * Callback invoked once for each parsed line.
 * Return 0 to stop reading early, or any non-zero value to continue.
 */
typedef int (*line_callback_t)(const log_line_t *line, void *userdata);

/*
 * Streams 'path' line by line, invoking 'callback' for each parsed line.
 * Returns 0 on success, -1 if the file cannot be opened.
 */
int file_reader_process(const char *path, line_callback_t callback, void *userdata);

#endif /* FILE_READER_H */

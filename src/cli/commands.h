/*
 * commands.h — Interface for the top-level command dispatcher.
 */

#ifndef COMMANDS_H
#define COMMANDS_H

#include "../logforge.h"

/*
 * Executes the command described by 'cfg'.
 * Returns 0 on success, 1 on error.
 */
int commands_run(const config_t *cfg);

#endif /* COMMANDS_H */

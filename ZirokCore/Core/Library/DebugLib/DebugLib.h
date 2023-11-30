/*
 * The DebugLib library is used to debug the core and display generation results at a stage when there is no graphical output.
 * Has three implementation instances:
 * DebugLib.cpp - allows you to print kernel logs to standard output.
 * DebugLibNull.cpp - this instance implements dummy functions; the instance is used by default in the release build.
 * DebugLibToFile.cpp - allows you to write logs to the log.txt file.
 */

#include "Core/BaseDef/BaseDef.h"

VOID
DebugPrintMessange(DEBUG_MESSANGE_TYPES Type,
                   STRING_VIEW String, ...);

VOID
DeadLoop();

VOID
InitLog();

VOID
DeInitLog();

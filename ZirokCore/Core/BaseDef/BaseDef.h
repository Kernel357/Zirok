#ifndef _BASE_TYPES_H
#define _BASE_TYPES_H

#include <map>
#include <string>
#include <vector>

/*==============================
  Base constants for Zirok Core
 ==============================*/


/* BASE TYPES */

#define VOID void
#define INT int
#define FLOAT float
#define DOUBLE double
#define BOOL bool
#define CHAR char
#define STRING std::string
#define STRING_VIEW std::string_view


/* === CORE SERVICE === */

#define LINE 0
#define COLUMN 1
#define SET 0
#define GET 1
#define COMPRESSED 0
#define EDITABLE 1
#define START_ROOM_MODE 0
#define DEFAULT_ROOM_MODE 1
#define NULL 0


/* === CLASSES ROOM === */

#define START_ROOM 1


/* === DOOR === */

#define DOOR_1 1
#define DOOR_2 2
#define DOOR_3 3
#define DOOR_4 4

#define CLOSE 0
#define OPEN 1
#define OCCUPIED 2
#define OUT_OF_FIELD 3

/* === PATTERNS === */

#define PATTERN_1 1
#define PATTERN_2 2
#define PATTERN_3 3
#define PATTERN_4 4
#define PATTERN_5 5
#define PATTERN_6 6
#define PATTERN_7 7
#define PATTERN_8 8


/*==========
  DEBUG LIB
 ==========*/

enum DEBUG_MESSANGE_TYPES
{
    INFO = 0,                                                               // Info for user.
    SERVICE_INFO,                                                           // Info for dev.
    WARN,                                                                   // Warning.
    ERROR                                                                   // Critical error.
};

extern std::vector<DEBUG_MESSANGE_TYPES> EnabledDebugMessangeTypes;         // You can change the contents of this vector (InitBaseDef.cpp), thereby configuring the logging levels.


/*=======
  STATUS
 =======*/

enum STATUS
{
    SUCCESS = 0,                                                            // Success!

    //ERRORS
    NO_FREE_CELLS,                                                          //  Not a single free cell left on the field.
    PARENT_ROOMS_NOT_FOUND,                                                 //  Could not find potential parent rooms.
    VECTOR_WITH_INCLUDED_PATTERNS_IS_EMPTY,                                 //  Vector with patterns empty.
    STARTING_ROOM_IS_OUTSIDE_THE_FIELD,                                     //  It turned out that the coordinates of the starting room are outside the grid.
    MORE_ROOMS_REQUIRED_TO_CREATE_A_STARTING_CROSS,                         //  The starting crosshair consists of 5 rooms, the number of rooms must be at least 5.
    FIELD_SIZE_IS_NOT_VALID,                                                //  Grid size is invalid.
    NUMBER_OF_ROOMS_IS_NOT_VALID,                                           //  Invalid number of rooms.
    FAILURE_TO_CREATE_START_CROSSHAIR,                                      //  An error occurred while creating the starting crosshair.
    STARTING_ROOM_CANNOT_BE_A_PARENT_ROOM,                                  /*  The starting room has no free directions and cannot be a parent room.
                                                                                    This was likely due to the fact that the field can only accommodate the starting room. */

    //WARNINGS
    FAILURE_TO_CREATE_ROOM_COORDINATES_ALREADY_BUSY,                        //  Room creation error: Coordinates already taken.
    FAILURE_TO_CREATE_ROOM_THE_DOOR_IN_THE_SELECTED_DIRECTION_IS_OPEN,      //  Room creation error: The direction chosen by the library has already been used, the door is open.
    FAILURE_TO_CREATE_ROOM_GOING_BEYOND_THE_FIELD,                          //  Room creation error: There was an exit from the field.
    FAILURE_TO_CREATE_ROOM_NO_FREE_CELLS,                                   //  Room creation error: The number of remaining cells is less than the cells included in the pattern.

    //SERVICE INFO
    ROOM_HAS_BEEN_REMOVED,                                                  //  The room has been removed from the _SortedParentRooms vector.
    ROOM_HAS_BEEN_ADDED,                                                    //  The room has been added to the _SortedParentRooms vector.
    ROOM_WAS_NOT_ADDED,                                                     //  The room was not added to the parent rooms vector.
    PATTERN_DOES_NOT_FIT,                                                   //  The pattern is not suitable as a pattern for the next child room.
};

extern std::map<INT, std::string> StatusMap;

extern std::map<INT, std::string>::iterator IteratorStatusMap;

extern VOID InitStatusMap();

#endif

#include "Core/Library/DebugLib/DebugLib.h"

using namespace std;

map<INT, STRING> StatusMap;
map<INT, STRING>::iterator IteratorStatusMap;

// You can change the contents of this vector, thereby configuring the logging levels.
std::vector<DEBUG_MESSANGE_TYPES> EnabledDebugMessangeTypes = {INFO,             // Info for user
                                                               /*SERVICE_INFO,*/ // Info for dev
                                                               /*WARN,*/         // Warnings
                                                               /*ERROR*/         // Errors
                                                               };

VOID InitStatusMap()
{
    DebugPrintMessange(INFO, "Initialization status map... \n");

    StatusMap[SUCCESS] = "SUCCESS";

    StatusMap[NO_FREE_CELLS] = "NO_FREE_CELLS";
    StatusMap[PARENT_ROOMS_NOT_FOUND] = "PARENT_ROOMS_NOT_FOUND";
    StatusMap[VECTOR_WITH_INCLUDED_PATTERNS_IS_EMPTY] = "VECTOR_WITH_INCLUDED_PATTERNS_IS_EMPTY";
    StatusMap[STARTING_ROOM_IS_OUTSIDE_THE_FIELD] = "STARTING_ROOM_IS_OUTSIDE_THE_FIELD";
    StatusMap[MORE_ROOMS_REQUIRED_TO_CREATE_A_STARTING_CROSS] = "MORE_ROOMS_REQUIRED_TO_CREATE_A_STARTING_CROSS";
    StatusMap[FIELD_SIZE_IS_NOT_VALID] = "FIELD_SIZE_IS_NOT_VALID";
    StatusMap[NUMBER_OF_ROOMS_IS_NOT_VALID] = "NUMBER_OF_ROOMS_IS_NOT_VALID";
    StatusMap[FAILURE_TO_CREATE_START_CROSSHAIR] = "FAILURE_TO_CREATE_START_CROSSHAIR";
    StatusMap[FAILURE_TO_CREATE_ROOM_COORDINATES_ALREADY_BUSY] = "FAILURE_TO_CREATE_ROOM_COORDINATES_ALREADY_BUSY";
    StatusMap[FAILURE_TO_CREATE_ROOM_THE_DOOR_IN_THE_SELECTED_DIRECTION_IS_OPEN] = "FAILURE_TO_CREATE_ROOM_THE_DOOR_IN_THE_SELECTED_DIRECTION_IS_OPEN";
    StatusMap[FAILURE_TO_CREATE_ROOM_GOING_BEYOND_THE_FIELD] = "FAILURE_TO_CREATE_ROOM_GOING_BEYOND_THE_FIELD";
    StatusMap[FAILURE_TO_CREATE_ROOM_NO_FREE_CELLS] = "FAILURE_TO_CREATE_ROOM_NO_FREE_CELLS";
    StatusMap[STARTING_ROOM_CANNOT_BE_A_PARENT_ROOM] = "STARTING_ROOM_CANNOT_BE_A_PARENT_ROOM";

    StatusMap[ROOM_HAS_BEEN_REMOVED] = "ROOM_HAS_BEEN_REMOVED";
    StatusMap[ROOM_HAS_BEEN_ADDED] = "ROOM_HAS_BEEN_ADDED";

    return;
}

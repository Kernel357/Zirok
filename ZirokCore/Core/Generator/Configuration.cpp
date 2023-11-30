/*
 * This file contains the implementation of the methods of the Generator class, which are responsible for configuring the core.
 * This is in particular the definition of class fields and checking values ​​for validity.
 */

#include "Generator.h"

/*
 * STATUS
 * Generator::Configure()
 *
 * We can use this method to configure the core.
 *
 * @params:
 *      INT FieldSizeLine
 *      INT FieldSizeColumn
 *      INT CoordinateStartRoomLine
 *      INT CoordinateStartRoomColumn
 *      INT NumberOfRooms
 *      BOOL UseStartCrosshair
 *      vector<INT> IncludedPatterns
 *
 * @return:
 *      Status: SUCCESS
 *              FIELD_SIZE_IS_NOT_VALID
 *              MORE_ROOMS_REQUIRED_TO_CREATE_A_STARTING_CROSS
 *              NUMBER_OF_ROOMS_IS_NOT_VALID
 *              STARTING_ROOM_IS_OUTSIDE_THE_FIELD
 *              VECTOR_WITH_INCLUDED_PATTERNS_IS_EMPTY
*/

STATUS
Generator::Configure(INT FieldSizeLine,
                     INT FieldSizeColumn,
                     INT CoordinateStartRoomLine,
                     INT CoordinateStartRoomColumn,
                     INT NumberOfRooms,
                     BOOL UseStartCrosshair,
                     vector<INT> IncludedPatterns)
{
    DebugPrintMessange(INFO, "Configuration core... \n");

    /*=================
      Core conf fields
     =================*/
    *_NumberOfRooms = NumberOfRooms;
    *_UseStartCrosshair = UseStartCrosshair;
    *_FieldSizeLine = FieldSizeLine;
    *_FieldSizeColumn = FieldSizeColumn;
    *_CoordinateStartRoomLine = CoordinateStartRoomLine;
    *_CoordinateStartRoomColumn = CoordinateStartRoomColumn;
    *_CellIterator = FieldSizeColumn * FieldSizeLine;
    _IncludedPatterns = IncludedPatterns;

    DebugPrintMessange(INFO, "Included pattern: ");
    for(INT i = 0; i < IncludedPatterns.size(); i++)
    {
        DebugPrintMessange(INFO, "%d ", IncludedPatterns.at(i));
    }

    VerifyParameter();

    if(*_Status != SUCCESS)
    {
        return *_Status;
    }

    /*=================
      Core conf fields
     =================*/
    _Rooms.resize(NumberOfRooms);
    _SortedParentRooms.resize(0);
    _OccupiedCellAddresses.resize(0);

    /*====================
      Core service fields
     ====================*/
    *_Direction = 0;
    *_RandomRoom = 0;
    *_CurrentRoom = 1;
    *_ChildRoomPattern = 0;

    return *_Status;
}



/*
 * VOID
 * Generator::VerifyParameter()
 *
 * We use this method to protect the core from a dead loop or undefined behavior
 *      during the dungeon generation phase due to incorrect parameters passed to it.
 *
 * @params:
 *
 * @return:
 *      Status: SUCCESS
 *              FIELD_SIZE_IS_NOT_VALID
 *              MORE_ROOMS_REQUIRED_TO_CREATE_A_STARTING_CROSS
 *              NUMBER_OF_ROOMS_IS_NOT_VALID
 *              STARTING_ROOM_IS_OUTSIDE_THE_FIELD
 *              VECTOR_WITH_INCLUDED_PATTERNS_IS_EMPTY
*/

VOID
Generator::VerifyParameter()
{  
    DebugPrintMessange(INFO, "\nVerification parameter... \n");

    if(*_FieldSizeColumn <= 0 ||
       *_FieldSizeColumn > 99 ||
       *_FieldSizeLine <= 0 ||
       *_FieldSizeLine > 99 ||
       *_CellIterator <= 0)
    {
        *_Status = FIELD_SIZE_IS_NOT_VALID;
        return;
    }

    if(*_UseStartCrosshair == true)
    {
        if(*_NumberOfRooms < 5)
        {
            *_Status = MORE_ROOMS_REQUIRED_TO_CREATE_A_STARTING_CROSS;
            return;
        }
    }

    else
    {
        if(*_NumberOfRooms <= 0)
        {
            *_Status = NUMBER_OF_ROOMS_IS_NOT_VALID;
            return;
        }
    }

    if (*_CoordinateStartRoomLine > *_FieldSizeLine ||
        *_CoordinateStartRoomLine <= 0 ||
        *_CoordinateStartRoomColumn > *_FieldSizeColumn ||
        *_CoordinateStartRoomColumn <= 0)
    {
        *_Status = STARTING_ROOM_IS_OUTSIDE_THE_FIELD;
        return;
    }

    if(_IncludedPatterns.empty())
    {
        *_Status = VECTOR_WITH_INCLUDED_PATTERNS_IS_EMPTY;
        return;
    }

    *_Status = SUCCESS;
    DebugPrintMessange(INFO, "\nStatus: %s \n", *_Status);
    return;
}

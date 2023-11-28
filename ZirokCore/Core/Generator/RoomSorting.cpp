/*
 * This file contains the implementation of methods of the Generator class responsible for preparing the vector with rooms for use by RandomLib.
 * This is in particular the addition of new rooms to the vector, as well as their removal if the room has no free directions.
 */

#include "Generator.h"
#include <iostream>

VOID
Generator::AddingRoomToVector(shared_ptr<BaseRoomPattern> Room)
{
    //Gathering information about the occupancy of the fields around the room

    DOUBLE Coordinates;
    INT Line;
    INT Column;

    for(INT i = 1; i <= 4; i++)
    {
        Coordinates = Room->SetOrGet_RoomCellCoordinates(1, i, 0);
        Line = TranslateCoordinates(EDITABLE, LINE, Coordinates, NULL, NULL);
        Column = TranslateCoordinates(EDITABLE, COLUMN, Coordinates, NULL, NULL);


        if(i == 1)
        {
            Line--;
        }

        else if(i == 2)
        {
            Column++;
        }

        else if(i == 3)
        {
            Line++;
        }

        else if(i == 4)
        {
            Column--;
        }

        Coordinates = TranslateCoordinates(0, 0, 0, Line, Column);

        if(IsOccupiedCoordinates(Coordinates) && Room->SetOrGet_OpenDoor(GET, i, NULL) != 1)
        {
            DebugPrintMessange(SERVICE_INFO, "Coordinates: %f is occupied and door is not open! \n", Coordinates);
            Room->SetOrGet_OpenDoor(0, i, 2);
        }

        else if(IsOutOfFieldCoordinates(Coordinates))
        {
            //DebugPrintMessange(INFO, "Coordinates: %f is out of field! \n", Coordinates);
            Room->SetOrGet_OpenDoor(0, i, 3);
        }
    }

    if(Room->Get_FreeDirections().empty())
    {
        DebugPrintMessange(SERVICE_INFO, "Room is not added to SortedRoomVector \n");
        *_Status = ROOM_WAS_NOT_ADDED;
        return;
    }

    _SortedParentRooms.push_back(Room);
    *_Status = SUCCESS;
    DebugPrintMessange(SERVICE_INFO, "Room is added to SortedRoomVector \n");
    return;
}

VOID
Generator::CheckingRoom(INT Room)
{
    DOUBLE Coordinates;
    INT Line;
    INT Column;

    for(INT i = 1; i <= 4; i++)
    {
        Coordinates = _SortedParentRooms.at(Room - 1)->SetOrGet_RoomCellCoordinates(1, i, 0);
        Line = TranslateCoordinates(EDITABLE, LINE, Coordinates, NULL, NULL);
        Column = TranslateCoordinates(EDITABLE, COLUMN, Coordinates, NULL, NULL);

        if(i == 1)
        {
            Line--;
        }

        else if(i == 2)
        {
            Column++;
        }

        else if(i == 3)
        {
            Line++;
        }

        else if(i == 4)
        {
            Column--;
        }

        Coordinates = TranslateCoordinates(COMPRESSED, NULL, NULL, Line, Column);

        if(IsOccupiedCoordinates(Coordinates) && _SortedParentRooms.at(Room - 1)->SetOrGet_OpenDoor(GET, i, NULL) != 1)
        {
            _SortedParentRooms.at(Room - 1)->SetOrGet_OpenDoor(SET, i, OCCUPIED);
        }

        else if(IsOutOfFieldCoordinates(Coordinates))
        {
            _SortedParentRooms.at(Room - 1)->SetOrGet_OpenDoor(SET, i, OUT_OF_FIELD);
        }
    }

    //If room hasn't free direction, we delete this room

    if(_SortedParentRooms.at(Room - 1)->Get_FreeDirections().empty())
    {
        DebugPrintMessange(INFO, "Room is removed from SortedRoomVector... \n");
        _SortedParentRooms.erase(_SortedParentRooms.begin() + (Room - 1));

        DebugPrintMessange(INFO, "Sorted parent room vector: ");

        for(INT i = 0; i < _SortedParentRooms.size(); i++)
        {
            DebugPrintMessange(INFO, "%d ", _SortedParentRooms.at(i)->Get_SerialNumber());
        }

        DebugPrintMessange(INFO, "\n");

        *_Status = ROOM_HAS_BEEN_REMOVED;
        return;
    }

    *_Status = SUCCESS;
    return;
}

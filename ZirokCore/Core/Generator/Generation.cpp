/*
 * This file contains the implementation of the methods of the Generator class responsible for generating the dungeon.
 */

#include <cstring>
#include <iostream>
#include <vector>
#include <algorithm>
#include "Generator.h"

using namespace std;

Generator::Generator()
{
    InitLog();

    DebugPrintMessange(INFO, "\nCreation core... \n");

    InitStatusMap();
}

Generator::~Generator()
{
    DebugPrintMessange(INFO, "\nDestruction core... \n");

    //Core service fields
    delete _Status;
    delete _Direction;
    delete _RandomRoom;
    delete _CurrentRoom;
    delete _ChildRoomPattern;

    //Core conf fields
    _Rooms.clear();
    _Rooms.shrink_to_fit();

    _OccupiedCellAddresses.clear();
    _OccupiedCellAddresses.shrink_to_fit(); 

    _SortedParentRooms.clear();
    _SortedParentRooms.shrink_to_fit();

    delete _UseStartCrosshair;
    delete _NumberOfRooms;
    delete _FieldSizeLine;
    delete _FieldSizeColumn;
    delete _CoordinateStartRoomColumn;
    delete _CoordinateStartRoomLine;
    delete _CellIterator;

    DeInitLog();
}


/*
 * This method will calculate the coordinates for new room cells depending on the pattern of the new room.
 *
 * @param:
 *      ChildRoomPattern = <pattern for child (new) room>;
 *
 *      Direction = <direction for create child (new) room>;
 *
 *      Line = <line coordinate>; In this parameter we set the line coordinate of
 *          the cell of the parent room in which the door is located in the direction we need.
 *
 *      Column = <column coordinate>; In this parameter we set the column coordinate of
 *          the cell of the parent room in which the door is located in the direction we need.
 *
 * @return:
 *      This method can return vector with cell coordinates for child (new) room.
*/

vector <vector<DOUBLE>>
Generator::CalculateOfRoomCellsCoordinates(INT Line,
                                           INT Column)
{
    vector <vector<DOUBLE>> RoomCellsCoordinates;
    DOUBLE Coordinates = 0;

    if(*_ChildRoomPattern == 1)
    {
        if(*_CellIterator - 1 < 0)
        {
            *_Status = FAILURE_TO_CREATE_ROOM_NO_FREE_CELLS;
            return RoomCellsCoordinates;
        }

        RoomCellsCoordinates.assign(1, vector<DOUBLE>(2));

        if(*_Direction == 1)
        {
            //First room cell
            Line = Line - 1;
        }

        else if(*_Direction == 2)
        {
            //First room cell
            Column = Column + 1;
        }

        else if(*_Direction == 3)
        {
            //First room cell
            Line = Line + 1;
        }

        else if(*_Direction == 4)
        {
            //First room cell
            Column = Column - 1;
        }        

        Coordinates = TranslateCoordinates(COMPRESSED, NULL, NULL, Line, Column);

        if(IsOutOfFieldCoordinates(Coordinates))
        {
            *_Status = FAILURE_TO_CREATE_ROOM_GOING_BEYOND_THE_FIELD;
            return RoomCellsCoordinates;
        }

        if(IsOccupiedCoordinates(Coordinates))
        {
            *_Status = FAILURE_TO_CREATE_ROOM_COORDINATES_ALREADY_BUSY;
            return RoomCellsCoordinates;
        }

        RoomCellsCoordinates.at(0).at(0) = Coordinates;
        RoomCellsCoordinates.at(0).at(1) = 1;

        DebugPrintMessange(INFO, "Coordinates: %f \n", Coordinates);

        _OccupiedCellAddresses.push_back(Coordinates);

        *_CellIterator = *_CellIterator - 1;

        *_Status = SUCCESS;
        return RoomCellsCoordinates;
    }

    ////////////WARNING!!! Test Part/////////////////////

    else if(*_ChildRoomPattern == 2)
    {
        if(*_CellIterator - 2 < 0)
        {
            *_Status = FAILURE_TO_CREATE_ROOM_NO_FREE_CELLS;
            return RoomCellsCoordinates;
        }

        RoomCellsCoordinates.assign(2, vector<DOUBLE>(2));

        for(INT i = 0; i < 2; i++)
        {
            if(*_Direction == 1)
            {
                if(i == 0)
                {
                    //First room cell
                    Line--;
                }

                else if(i == 1)
                {
                    //Second room cell
                    Line--;
                }
            }

            else if(*_Direction == 2)
            {
                if(i == 0)
                {
                    //First room cell
                    Column++;
                }

                else if(i == 1)
                {
                    //Second room cell
                    Line--;
                }
            }

            else if(*_Direction == 3)
            {
                if(i == 0)
                {
                    //First room cell
                    Line++;
                }

                else if(i == 1)
                {
                    //Second room cell
                    Line++;
                }
            }

            else if(*_Direction == 4)
            {
                if(i == 0)
                {
                    //First room cell
                    Column--;
                }

                else if(i == 1)
                {
                    //Second room cell
                    Line++;
                }
            }

            Coordinates = TranslateCoordinates(COMPRESSED, NULL, NULL, Line, Column);

            if(IsOutOfFieldCoordinates(Coordinates))
            {
                *_Status = FAILURE_TO_CREATE_ROOM_GOING_BEYOND_THE_FIELD;
                return RoomCellsCoordinates;
            }

            if(IsOccupiedCoordinates(Coordinates))
            {
                *_Status = FAILURE_TO_CREATE_ROOM_COORDINATES_ALREADY_BUSY;
                return RoomCellsCoordinates;
            }

            RoomCellsCoordinates.at(i).at(0) = Coordinates;

            if(*_Direction == 1 || *_Direction == 2)
            {
                if(i == 0)
                {
                    RoomCellsCoordinates.at(i).at(1) = 3;
                }
                else if(i == 1)
                {
                    RoomCellsCoordinates.at(i).at(1) = 1;
                }
            }

            else if(*_Direction == 3 || *_Direction == 4)
            {
                if(i == 0)
                {
                    RoomCellsCoordinates.at(i).at(1) = 1;
                }
                else if(i == 1)
                {
                    RoomCellsCoordinates.at(i).at(1) = 3;
                }
            }

            DebugPrintMessange(INFO, "Coordinates: %f \n", Coordinates);
        }

        for(INT i = 0; i < RoomCellsCoordinates.size(); i++)
        {
            Coordinates = RoomCellsCoordinates.at(i).at(0);
            _OccupiedCellAddresses.push_back(Coordinates);
        }

        *_CellIterator = *_CellIterator - 2;

        *_Status = SUCCESS;
        return RoomCellsCoordinates;
    }

    else if(*_ChildRoomPattern == 3)
    {
        if(*_CellIterator - 2 < 0)
        {
            *_Status = FAILURE_TO_CREATE_ROOM_NO_FREE_CELLS;
            return RoomCellsCoordinates;
        }

        RoomCellsCoordinates.assign(2, vector<DOUBLE>(2));

        for(INT i = 0; i < 2; i++)
        {
            if(*_Direction == 1)
            {
                if(i == 0)
                {
                    //First room cell
                    Line--;
                }

                else if(i == 1)
                {
                    //Second room cell
                    Column--;
                }
            }

            else if(*_Direction == 2)
            {
                if(i == 0)
                {
                    //First room cell
                    Column++;
                }

                else if(i == 1)
                {
                    //Second room cell
                    Column++;
                }
            }

            else if(*_Direction == 3)
            {
                if(i == 0)
                {
                    //First room cell
                    Line++;
                }

                else if(i == 1)
                {
                    //Second room cell
                    Column++;
                }
            }

            else if(*_Direction == 4)
            {
                if(i == 0)
                {
                    //First room cell
                    Column--;
                }

                else if(i == 1)
                {
                    //Second room cell
                    Column--;
                }
            }

            Coordinates = TranslateCoordinates(COMPRESSED, NULL, NULL, Line, Column);

            if(IsOutOfFieldCoordinates(Coordinates))
            {
                *_Status = FAILURE_TO_CREATE_ROOM_GOING_BEYOND_THE_FIELD;
                return RoomCellsCoordinates;
            }

            if(IsOccupiedCoordinates(Coordinates))
            {
                *_Status = FAILURE_TO_CREATE_ROOM_COORDINATES_ALREADY_BUSY;
                return RoomCellsCoordinates;
            }

            RoomCellsCoordinates.at(i).at(0) = Coordinates;

            if(*_Direction == 1 || *_Direction == 4)
            {
                if(i == 0)
                {
                    RoomCellsCoordinates.at(i).at(1) = 2;
                }
                else if(i == 1)
                {
                    RoomCellsCoordinates.at(i).at(1) = 1;
                }
            }

            else if(*_Direction == 2 || *_Direction == 3)
            {
                if(i == 0)
                {
                    RoomCellsCoordinates.at(i).at(1) = 1;
                }
                else if(i == 1)
                {
                    RoomCellsCoordinates.at(i).at(1) = 2;
                }
            }

            DebugPrintMessange(INFO, "Coordinates: %f \n", Coordinates);
        }

        for(INT i = 0; i < RoomCellsCoordinates.size(); i++)
        {
            Coordinates = RoomCellsCoordinates.at(i).at(0);
            _OccupiedCellAddresses.push_back(Coordinates);
        }

        *_CellIterator = *_CellIterator - 2;

        *_Status = SUCCESS;
        return RoomCellsCoordinates;
    }
    ////////////WARNING!!! Test Part/////////////////////

    else if(*_ChildRoomPattern == 4)
    {
        if(*_CellIterator - 3 < 0)
        {
            *_Status = FAILURE_TO_CREATE_ROOM_NO_FREE_CELLS;
            return RoomCellsCoordinates;
        }

        RoomCellsCoordinates.assign(3, vector<DOUBLE>(2));

        for(INT i = 0; i < 3; i++)
        {
            if(*_Direction == 1)
            {
                if(i == 0)
                {
                    //First room cell
                    Line--;
                }

                else if(i == 1)
                {
                    //Second room cell
                    Line--;
                }

                else if(i == 2)
                {
                    //Third room cell
                    Column++;
                }
            }

            else if(*_Direction == 2)
            {
                if(i == 0)
                {
                    //First room cell
                    Column++;
                }

                else if(i == 1)
                {
                    //Second room cell
                    Line--;
                }

                else if(i == 2)
                {
                    //Third room cell
                    Column++;
                }
            }

            else if(*_Direction == 3)
            {
                if(i == 0)
                {
                    //First room cell
                    Line++;
                }

                else if(i == 1)
                {
                    //Second room cell
                    Column--;
                }

                else if(i == 2)
                {
                    //Third room cell
                    Line++;
                }
            }

            else if(*_Direction == 4)
            {
                if(i == 0)
                {
                    //First room cell
                    Column--;
                }

                else if(i == 1)
                {
                    //Second room cell
                    Column--;
                }

                else if(i == 2)
                {
                    //Third room cell
                    Line++;
                }
            }

            Coordinates = TranslateCoordinates(COMPRESSED, NULL, NULL, Line, Column);

            if(IsOutOfFieldCoordinates(Coordinates))
            {
                *_Status = FAILURE_TO_CREATE_ROOM_GOING_BEYOND_THE_FIELD;
                return RoomCellsCoordinates;
            }

            if(IsOccupiedCoordinates(Coordinates))
            {
                *_Status = FAILURE_TO_CREATE_ROOM_COORDINATES_ALREADY_BUSY;
                return RoomCellsCoordinates;
            }

            RoomCellsCoordinates.at(i).at(0) = Coordinates;

            if(*_Direction == 1 || *_Direction == 2)
            {
                if(i == 0)
                {
                    RoomCellsCoordinates.at(i).at(1) = 3;
                }
                else if(i == 2)
                {
                    RoomCellsCoordinates.at(i).at(1) = 1;
                }
            }

            else if(*_Direction == 3 || *_Direction == 4)
            {
                if(i == 0)
                {
                    RoomCellsCoordinates.at(i).at(1) = 1;
                }
                else if(i == 2)
                {
                    RoomCellsCoordinates.at(i).at(1) = 3;
                }
            }

            DebugPrintMessange(INFO, "Coordinates: %f \n", Coordinates);
        }

        for(INT i = 0; i < RoomCellsCoordinates.size(); i++)
        {
            Coordinates = RoomCellsCoordinates.at(i).at(0);
            _OccupiedCellAddresses.push_back(Coordinates);
        }

        *_CellIterator = *_CellIterator - 3;

        *_Status = SUCCESS;
        return RoomCellsCoordinates;
    }

    else if(*_ChildRoomPattern == 5)
    {
        if(*_CellIterator - 3 < 0)
        {
            *_Status = FAILURE_TO_CREATE_ROOM_NO_FREE_CELLS;
            return RoomCellsCoordinates;
        }

        RoomCellsCoordinates.assign(3, vector<DOUBLE>(2));

        for(INT i = 0; i < 3; i++)
        {
            if(*_Direction == 1)
            {
                if(i == 0)
                {
                    //First room cell
                    Line--;
                }

                else if(i == 1)
                {
                    //Second room cell
                    Column--;
                }

                else if(i == 2)
                {
                    //Third room cell
                    Line--;
                }
            }

            else if(*_Direction == 2)
            {
                if(i == 0)
                {
                    //First room cell
                    Column++;
                }

                else if(i == 1)
                {
                    //Second room cell
                    Line++;
                }

                else if(i == 2)
                {
                    //Third room cell
                    Column++;
                }
            }

            else if(*_Direction == 3)
            {
                if(i == 0)
                {
                    //First room cell
                    Line++;
                }

                else if(i == 1)
                {
                    //Second room cell
                    Line++;
                }

                else if(i == 2)
                {
                    //Third room cell
                    Column++;
                }
            }

            else if(*_Direction == 4)
            {
                if(i == 0)
                {
                    //First room cell
                    Column--;
                }

                else if(i == 1)
                {
                    //Second room cell
                    Column--;
                }

                else if(i == 2)
                {
                    //Third room cell
                    Line--;
                }
            }

            Coordinates = TranslateCoordinates(COMPRESSED, NULL, NULL, Line, Column);

            if(IsOutOfFieldCoordinates(Coordinates))
            {
                *_Status = FAILURE_TO_CREATE_ROOM_GOING_BEYOND_THE_FIELD;
                return RoomCellsCoordinates;
            }

            if(IsOccupiedCoordinates(Coordinates))
            {
                *_Status = FAILURE_TO_CREATE_ROOM_COORDINATES_ALREADY_BUSY;
                return RoomCellsCoordinates;
            }

            RoomCellsCoordinates.at(i).at(0) = Coordinates;

            if(*_Direction == 1 || *_Direction == 4)
            {
                if(i == 0)
                {
                    RoomCellsCoordinates.at(i).at(1) = 2;
                }
                else if(i == 2)
                {
                    RoomCellsCoordinates.at(i).at(1) = 1;
                }
            }

            else if(*_Direction == 2 || *_Direction == 3)
            {
                if(i == 0)
                {
                    RoomCellsCoordinates.at(i).at(1) = 1;
                }
                else if(i == 2)
                {
                    RoomCellsCoordinates.at(i).at(1) = 2;
                }
            }

            DebugPrintMessange(INFO, "Coordinates: %f \n", Coordinates);
        }

        for(INT i = 0; i < RoomCellsCoordinates.size(); i++)
        {
            Coordinates = RoomCellsCoordinates.at(i).at(0);
            _OccupiedCellAddresses.push_back(Coordinates);
        }

        *_CellIterator = *_CellIterator - 3;

        *_Status = SUCCESS;
        return RoomCellsCoordinates;
    }
    ////////////WARNING!!! Test Part/////////////////////

    else if(*_ChildRoomPattern == 6)
    {
        if(*_CellIterator - 3 < 0)
        {
            *_Status = FAILURE_TO_CREATE_ROOM_NO_FREE_CELLS;
            return RoomCellsCoordinates;
        }

        RoomCellsCoordinates.assign(3, vector<DOUBLE>(2));

        for(INT i = 0; i < 3; i++)
        {
            if(*_Direction == 1)
            {
                if(i == 0)
                {
                    //First room cell
                    Line--;
                }

                else if(i == 1)
                {
                    //Second room cell
                    Line--;
                }

                else if(i == 2)
                {
                    //Third room cell
                    Column--;
                }
            }

            else if(*_Direction == 2)
            {
                if(i == 0)
                {
                    //First room cell
                    Column++;
                }

                else if(i == 1)
                {
                    //Second room cell
                    Column++;
                }

                else if(i == 2)
                {
                    //Third room cell
                    Line++;
                }
            }

            else if(*_Direction == 3)
            {
                if(i == 0)
                {
                    //First room cell
                    Line++;
                }

                else if(i == 1)
                {
                    //Second room cell
                    Column++;
                }

                else if(i == 2)
                {
                    //Third room cell
                    Line++;
                }
            }

            else if(*_Direction == 4)
            {
                if(i == 0)
                {
                    //First room cell
                    Column--;
                }

                else if(i == 1)
                {
                    //Second room cell
                    Line--;
                }

                else if(i == 2)
                {
                    //Third room cell
                    Column--;
                }
            }

            Coordinates = TranslateCoordinates(COMPRESSED, NULL, NULL, Line, Column);

            if(IsOutOfFieldCoordinates(Coordinates))
            {
                *_Status = FAILURE_TO_CREATE_ROOM_GOING_BEYOND_THE_FIELD;
                return RoomCellsCoordinates;
            }

            if(IsOccupiedCoordinates(Coordinates))
            {
                *_Status = FAILURE_TO_CREATE_ROOM_COORDINATES_ALREADY_BUSY;
                return RoomCellsCoordinates;
            }

            RoomCellsCoordinates.at(i).at(0) = Coordinates;

            if(*_Direction == 2 || *_Direction == 3)
            {
                if(i == 0)
                {
                    RoomCellsCoordinates.at(i).at(1) = 1;
                }
                else if(i == 2)
                {
                    RoomCellsCoordinates.at(i).at(1) = 2;
                }
            }

            else if(*_Direction == 1 || *_Direction == 4)
            {
                if(i == 0)
                {
                    RoomCellsCoordinates.at(i).at(1) = 2;
                }
                else if(i == 2)
                {
                    RoomCellsCoordinates.at(i).at(1) = 1;
                }
            }

            DebugPrintMessange(INFO, "Coordinates: %f \n", Coordinates);
        }

        for(INT i = 0; i < RoomCellsCoordinates.size(); i++)
        {
            Coordinates = RoomCellsCoordinates.at(i).at(0);
            _OccupiedCellAddresses.push_back(Coordinates);
        }

        *_CellIterator = *_CellIterator - 3;

        *_Status = SUCCESS;
        return RoomCellsCoordinates;
    }

    else if(*_ChildRoomPattern == 7)
    {
        if(*_CellIterator - 3 < 0)
        {
            *_Status = FAILURE_TO_CREATE_ROOM_NO_FREE_CELLS;
            return RoomCellsCoordinates;
        }

        RoomCellsCoordinates.assign(3, vector<DOUBLE>(2));

        for(INT i = 0; i < 3; i++)
        {
            if(*_Direction == 1)
            {
                if(i == 0)
                {
                    //First room cell
                    Line--;
                }

                else if(i == 1)
                {
                    //Second room cell
                    Column++;
                }

                else if(i == 2)
                {
                    //Third room cell
                    Line--;
                }
            }

            else if(*_Direction == 2)
            {
                if(i == 0)
                {
                    //First room cell
                    Column++;
                }

                else if(i == 1)
                {
                    //Second room cell
                    Column++;
                }

                else if(i == 2)
                {
                    //Third room cell
                    Line--;
                }
            }

            else if(*_Direction == 3)
            {
                if(i == 0)
                {
                    //First room cell
                    Line++;
                }

                else if(i == 1)
                {
                    //Second room cell
                    Line++;
                }

                else if(i == 2)
                {
                    //Third room cell
                    Column--;
                }
            }

            else if(*_Direction == 4)
            {
                if(i == 0)
                {
                    //First room cell
                    Column--;
                }

                else if(i == 1)
                {
                    //Second room cell
                    Line++;
                }

                else if(i == 2)
                {
                    //Third room cell
                    Column--;
                }
            }

            Coordinates = TranslateCoordinates(COMPRESSED, NULL, NULL, Line, Column);

            if(IsOutOfFieldCoordinates(Coordinates))
            {
                *_Status = FAILURE_TO_CREATE_ROOM_GOING_BEYOND_THE_FIELD;
                return RoomCellsCoordinates;
            }

            if(IsOccupiedCoordinates(Coordinates))
            {
                *_Status = FAILURE_TO_CREATE_ROOM_COORDINATES_ALREADY_BUSY;
                return RoomCellsCoordinates;
            }

            RoomCellsCoordinates.at(i).at(0) = Coordinates;

            if(*_Direction == 1 || *_Direction == 2)
            {
                if(i == 0)
                {
                    RoomCellsCoordinates.at(i).at(1) = 3;
                }
                else if(i == 2)
                {
                    RoomCellsCoordinates.at(i).at(1) = 1;
                }
            }

            else if(*_Direction == 3 || *_Direction == 4)
            {
                if(i == 0)
                {
                    RoomCellsCoordinates.at(i).at(1) = 1;
                }
                else if(i == 2)
                {
                    RoomCellsCoordinates.at(i).at(1) = 3;
                }
            }

            DebugPrintMessange(INFO, "Coordinates: %f \n", Coordinates);
        }

        for(INT i = 0; i < RoomCellsCoordinates.size(); i++)
        {
            Coordinates = RoomCellsCoordinates.at(i).at(0);
            _OccupiedCellAddresses.push_back(Coordinates);
        }

        *_CellIterator = *_CellIterator - 3;

        *_Status = SUCCESS;
        return RoomCellsCoordinates;
    }

    else if(*_ChildRoomPattern == 8)
    {
        if(*_CellIterator - 4 < 0)
        {
            *_Status = FAILURE_TO_CREATE_ROOM_NO_FREE_CELLS;
            return RoomCellsCoordinates;
        }

        RoomCellsCoordinates.assign(4, vector<DOUBLE>(2));

        for(INT i = 0; i < 4; i++)
        {
            if(*_Direction == 1)
            {
                if(i == 0)
                {
                    //First room cell
                    Line--;
                }

                else if(i == 1)
                {
                    //Second room cell
                    Line--;
                }

                else if(i == 2)
                {
                    //Third room cell
                    Column++;
                }

                else if(i == 3)
                {
                    //Fourth room cell
                    Line++;
                }
            }

            else if(*_Direction == 2)
            {
                if(i == 0)
                {
                    //First room cell
                    Column++;
                }

                else if(i == 1)
                {
                    //Second room cell
                    Column++;
                }

                else if(i == 2)
                {
                    //Third room cell
                    Line++;
                }

                else if(i == 3)
                {
                    //Fourth room cell
                    Column--;
                }
            }

            else if(*_Direction == 3)
            {
                if(i == 0)
                {
                    //First room cell
                    Line++;
                }

                else if(i == 1)
                {
                    //Second room cell
                    Line++;
                }

                else if(i == 2)
                {
                    //Third room cell
                    Column--;
                }

                else if(i == 3)
                {
                    //Fourth room cell
                    Line--;
                }
            }

            else if(*_Direction == 4)
            {
                if(i == 0)
                {
                    //First room cell
                    Column--;
                }

                else if(i == 1)
                {
                    //Second room cell
                    Column--;
                }

                else if(i == 2)
                {
                    //Third room cell
                    Line--;
                }

                else if(i == 3)
                {
                    //Fourth room cell
                    Column++;
                }
            }

            Coordinates = TranslateCoordinates(COMPRESSED, NULL, NULL, Line, Column);

            if(IsOutOfFieldCoordinates(Coordinates))
            {
                *_Status = FAILURE_TO_CREATE_ROOM_GOING_BEYOND_THE_FIELD;
                return RoomCellsCoordinates;
            }

            if(IsOccupiedCoordinates(Coordinates))
            {
                *_Status = FAILURE_TO_CREATE_ROOM_COORDINATES_ALREADY_BUSY;
                return RoomCellsCoordinates;
            }

            RoomCellsCoordinates.at(i).at(0) = Coordinates;

            if(*_Direction == 1)
            {
                if(i == 0)
                {
                    RoomCellsCoordinates.at(i).at(1) = 3;
                }

                else if(i == 1)
                {
                    RoomCellsCoordinates.at(i).at(1) = 4;
                }

                else if(i == 2)
                {
                    RoomCellsCoordinates.at(i).at(1) = 1;
                }

                else if(i == 3)
                {
                    RoomCellsCoordinates.at(i).at(1) = 2;
                }
            }

            else if(*_Direction == 2)
            {
                if(i == 0)
                {
                    RoomCellsCoordinates.at(i).at(1) = 4;
                }

                else if(i == 1)
                {
                    RoomCellsCoordinates.at(i).at(1) = 1;
                }

                else if(i == 2)
                {
                    RoomCellsCoordinates.at(i).at(1) = 2;
                }

                else if(i == 3)
                {
                    RoomCellsCoordinates.at(i).at(1) = 3;
                }
            }

            else if(*_Direction == 3)
            {
                if(i == 0)
                {
                    RoomCellsCoordinates.at(i).at(1) = 1;
                }

                else if(i == 1)
                {
                    RoomCellsCoordinates.at(i).at(1) = 2;
                }

                else if(i == 2)
                {
                    RoomCellsCoordinates.at(i).at(1) = 3;
                }

                else if(i == 3)
                {
                    RoomCellsCoordinates.at(i).at(1) = 4;
                }
            }

            else if(*_Direction == 4)
            {
                if(i == 0)
                {
                    RoomCellsCoordinates.at(i).at(1) = 2;
                }

                else if(i == 1)
                {
                    RoomCellsCoordinates.at(i).at(1) = 3;
                }

                else if(i == 2)
                {
                    RoomCellsCoordinates.at(i).at(1) = 4;
                }

                else if(i == 3)
                {
                    RoomCellsCoordinates.at(i).at(1) = 1;
                }
            }

            DebugPrintMessange(INFO, "Coordinates: %f \n", Coordinates);
        }

        for(INT i = 0; i < RoomCellsCoordinates.size(); i++)
        {
            Coordinates = RoomCellsCoordinates.at(i).at(0);
            _OccupiedCellAddresses.push_back(Coordinates);
        }

        *_CellIterator = *_CellIterator - 4;

        *_Status = SUCCESS;
        return RoomCellsCoordinates;
    }

    return RoomCellsCoordinates;
}

VOID
Generator::CreateRoom(INT RoomMode)
{
    if(RoomMode == 0)
    {
        //Create room
        _Rooms.at(*_CurrentRoom - 1) = make_shared<RoomPattern_1>(*_CurrentRoom);

        _Rooms.at(*_CurrentRoom - 1)->SetOrGet_RoomCellCoordinates(SET,
                                                                   DOOR_1,
                                                                   TranslateCoordinates(COMPRESSED,
                                                                                        NULL,
                                                                                        NULL,
                                                                                        *_CoordinateStartRoomLine,
                                                                                        *_CoordinateStartRoomColumn));
        _Rooms.at(*_CurrentRoom - 1)->SetOrGet_RoomClass(SET, START_ROOM);

        AddingRoomToVector(_Rooms.at(*_CurrentRoom - 1));
        if(*_Status != SUCCESS)
        {
            *_Status = STARTING_ROOM_CANNOT_BE_A_PARENT_ROOM;
        }

        _OccupiedCellAddresses.push_back(TranslateCoordinates(COMPRESSED, NULL, NULL, *_CoordinateStartRoomLine, *_CoordinateStartRoomColumn));
        *_CellIterator = *_CellIterator - 1;
        *_CurrentRoom = *_CurrentRoom + 1;
    }

    else
    {
        //Checking if the door is closed in the selected direction, if it is open, it makes no sense for us to try to put another room in the same place
        if((_SortedParentRooms.at(*_RandomRoom - 1)->SetOrGet_OpenDoor(GET, *_Direction, NULL)) != 0)
        {
            *_Status = FAILURE_TO_CREATE_ROOM_THE_DOOR_IN_THE_SELECTED_DIRECTION_IS_OPEN;
            return;
        }

        CheckingRoom(*_RandomRoom);

        if(*_Status == ROOM_HAS_BEEN_REMOVED)
        {
            return;
        }

        DOUBLE ParentCoordinateRoomCell = _SortedParentRooms.at(*_RandomRoom - 1)->SetOrGet_RoomCellCoordinates(GET, *_Direction, NULL);

        INT Line = TranslateCoordinates(EDITABLE, LINE, ParentCoordinateRoomCell, NULL, NULL);

        INT Column = TranslateCoordinates(EDITABLE, COLUMN, ParentCoordinateRoomCell, NULL, NULL);

        vector <vector<DOUBLE>> ChildRoomCellsCoordinates = CalculateOfRoomCellsCoordinates(Line, Column);

        if(*_Status != SUCCESS)
        {
            return;
        }


        if(*_ChildRoomPattern == 1)
        {
            _Rooms.at(*_CurrentRoom - 1) = make_shared<RoomPattern_1>(*_CurrentRoom);
            _Rooms.at(*_CurrentRoom - 1)->SetOrGet_RoomCellCoordinates(SET, ChildRoomCellsCoordinates.at(0).at(1), ChildRoomCellsCoordinates.at(0).at(0));
        }

        else if(*_ChildRoomPattern == 2)
        {
            _Rooms.at(*_CurrentRoom - 1) = make_shared<RoomPattern_2>(*_CurrentRoom);

            for(INT i = 0; i < 2; i++)
            {
                _Rooms.at(*_CurrentRoom - 1)->SetOrGet_RoomCellCoordinates(SET, ChildRoomCellsCoordinates.at(i).at(1), ChildRoomCellsCoordinates.at(i).at(0));
            }
        }

        else if(*_ChildRoomPattern == 3)
        {
            _Rooms.at(*_CurrentRoom - 1) = make_shared<RoomPattern_3>(*_CurrentRoom);

            for(INT i = 0; i < 2; i++)
            {
                _Rooms.at(*_CurrentRoom - 1)->SetOrGet_RoomCellCoordinates(SET, ChildRoomCellsCoordinates.at(i).at(1), ChildRoomCellsCoordinates.at(i).at(0));
            }
        }

        else if(*_ChildRoomPattern == 4)
        {
            _Rooms.at(*_CurrentRoom - 1) = make_shared<RoomPattern_4>(*_CurrentRoom);

            for(INT i = 0; i < 3; i++)
            {
                _Rooms.at(*_CurrentRoom - 1)->SetOrGet_RoomCellCoordinates(SET, ChildRoomCellsCoordinates.at(i).at(1), ChildRoomCellsCoordinates.at(i).at(0));
            }
        }

        else if(*_ChildRoomPattern == 5)
        {
            _Rooms.at(*_CurrentRoom - 1) = make_shared<RoomPattern_5>(*_CurrentRoom);

            for(INT i = 0; i < 3; i++)
            {
                _Rooms.at(*_CurrentRoom - 1)->SetOrGet_RoomCellCoordinates(SET, ChildRoomCellsCoordinates.at(i).at(1), ChildRoomCellsCoordinates.at(i).at(0));
            }
        }

        else if(*_ChildRoomPattern == 6)
        {
            _Rooms.at(*_CurrentRoom - 1) = make_shared<RoomPattern_6>(*_CurrentRoom);

            for(INT i = 0; i < 3; i++)
            {
                _Rooms.at(*_CurrentRoom - 1)->SetOrGet_RoomCellCoordinates(SET, ChildRoomCellsCoordinates.at(i).at(1), ChildRoomCellsCoordinates.at(i).at(0));
            }
        }

        else if(*_ChildRoomPattern == 7)
        {
            _Rooms.at(*_CurrentRoom - 1) = make_shared<RoomPattern_7>(*_CurrentRoom);

            for(INT i = 0; i < 3; i++)
            {
                _Rooms.at(*_CurrentRoom - 1)->SetOrGet_RoomCellCoordinates(SET, ChildRoomCellsCoordinates.at(i).at(1), ChildRoomCellsCoordinates.at(i).at(0));
            }
        }

        else if(*_ChildRoomPattern == 8)
        {
            _Rooms.at(*_CurrentRoom - 1) = make_shared<RoomPattern_8>(*_CurrentRoom);

            for(INT i = 0; i < 4; i++)
            {
                _Rooms.at(*_CurrentRoom - 1)->SetOrGet_RoomCellCoordinates(SET, ChildRoomCellsCoordinates.at(i).at(1), ChildRoomCellsCoordinates.at(i).at(0));
            }
        }


        //Depending on the direction of room generation, we open the corresponding doors

        if(*_Direction == 1)
        {
            //Open door in parent room
            _SortedParentRooms.at(*_RandomRoom - 1)->SetOrGet_OpenDoor(SET, DOOR_1, OPEN);

            //Open door in child room
            _Rooms.at(*_CurrentRoom - 1)->SetOrGet_OpenDoor(SET, DOOR_3, OPEN);
        }

        else if(*_Direction == 2)
        {
            //Open door in parent room
            _SortedParentRooms.at(*_RandomRoom - 1)->SetOrGet_OpenDoor(SET, DOOR_2, OPEN);

            //Open door in child room
            _Rooms.at(*_CurrentRoom - 1)->SetOrGet_OpenDoor(SET, DOOR_4, OPEN);
        }

        else if(*_Direction == 3)
        {
            //Open door in parent room
            _SortedParentRooms.at(*_RandomRoom - 1)->SetOrGet_OpenDoor(SET, DOOR_3, OPEN);

            //Open door in child room
            _Rooms.at(*_CurrentRoom - 1)->SetOrGet_OpenDoor(SET, DOOR_1, OPEN);
        }

        else if(*_Direction == 4)
        {
            //Open door in parent room
            _SortedParentRooms.at(*_RandomRoom - 1)->SetOrGet_OpenDoor(SET, DOOR_4, OPEN);

            //Open door in child room
            _Rooms.at(*_CurrentRoom - 1)->SetOrGet_OpenDoor(SET, DOOR_2, OPEN);
        }


        //Adding a new room to a vector with sorted rooms for RandomLib

        AddingRoomToVector(_Rooms.at(*_CurrentRoom - 1));


        //Checking the current parent room for the possibility of becoming a parent room in the future

        CheckingRoom(*_RandomRoom);

        *_Status = SUCCESS;
        *_CurrentRoom = *_CurrentRoom + 1;
    }

    return;
}

VOID
Generator::CreateStartCrosshair()
{
    DebugPrintMessange(INFO, "\nCreation start crosshair... \n");

    for(INT i = 1; i < 5; i++)
    {
        DebugPrintMessange(INFO, "Current room: %d \n", *_CurrentRoom);

        *_ChildRoomPattern = 1;
        *_Direction = i;
        *_RandomRoom = 1;
        CreateRoom(1);

        if(*_Status != SUCCESS)
        {
            *_Status = FAILURE_TO_CREATE_START_CROSSHAIR;
            return;
        }        
    }

    *_Status = SUCCESS;
    return;
}

STATUS
Generator::Generate()
{
    DebugPrintMessange(INFO, "\nNumber of room: %d \n", *_NumberOfRooms);

    DebugPrintMessange(INFO, "Current room: %d \n", *_CurrentRoom);

    //Create start room
    CreateRoom(START_ROOM_MODE);
    if(*_Status != SUCCESS)
    {
        return *_Status;
    }

    //Create start crosshair
    if(*_UseStartCrosshair)
    {
        CreateStartCrosshair();
        if(*_Status != SUCCESS)
        {
            return *_Status;
        }
    }

    vector<INT> SortedPatterns;

    while(*_CurrentRoom <= *_NumberOfRooms)
    {
        if(*_Status != SUCCESS)
        {
            break;
        }

        if(*_CellIterator == 0)
        {
            *_Status = NO_FREE_CELLS;
            break;
        }

        if(_SortedParentRooms.size() == 0)
        {
            *_Status = PARENT_ROOMS_NOT_FOUND;
            break;
        }

        DebugPrintMessange(INFO, "\nCurrent room: %d \n", *_CurrentRoom);

        *_RandomRoom = Get_RandomRoom(_SortedParentRooms);

        DebugPrintMessange(INFO, "Random room: %d \n", _SortedParentRooms.at(*_RandomRoom - 1)->Get_SerialNumber());

        *_Direction = Get_RandomDirection(_SortedParentRooms.at(*_RandomRoom - 1));
        DebugPrintMessange(INFO, "Direction: %d \n", *_Direction);

        SortedPatterns = TestingAndSortingPatterns(_SortedParentRooms.at(*_RandomRoom - 1), *_Direction);
        if(SortedPatterns.empty())
        {
            DebugPrintMessange(INFO, "SortedPatterns is empty! \n");
            *_Status = SUCCESS;
            continue;
        }

        *_ChildRoomPattern = Get_RandomPattern(SortedPatterns);
        DebugPrintMessange(INFO, "Pattern: %d \n", *_ChildRoomPattern);

        CreateRoom(DEFAULT_ROOM_MODE);

        if(*_Status != SUCCESS)
        {
            DebugPrintMessange(WARN, "Status: %s\n", *_Status);
            *_Status = SUCCESS;
            continue;
        }

        *_Status = SUCCESS;
    }

    if(*_Status != SUCCESS)
    {
         return *_Status;
    }

    TestShow();

    return *_Status;
}

VOID
Generator::TestShow()
{
    vector<DOUBLE> Cells;
    for(INT i = 0; i < *_NumberOfRooms; i++)
    {
        DebugPrintMessange(INFO, "\nRoom number: %d \n", (i + 1));
        Cells = _Rooms.at(i)->Get_RoomCellsCoordinates();

        for(INT d = 0; d < Cells.size(); d++)
        {
            DebugPrintMessange(INFO, "Room cell coordinates: %f \n", Cells.at(d));
        }

        DebugPrintMessange(INFO, "Pattern: %d \n", _Rooms.at(i)->Get_Pattern());
        DebugPrintMessange(INFO, "Door 1: %d \n", _Rooms.at(i)->SetOrGet_OpenDoor(1, 1, 0));
        DebugPrintMessange(INFO, "Door 2: %d \n", _Rooms.at(i)->SetOrGet_OpenDoor(1, 2, 0));
        DebugPrintMessange(INFO, "Door 3: %d \n", _Rooms.at(i)->SetOrGet_OpenDoor(1, 3, 0));
        DebugPrintMessange(INFO, "Door 4: %d \n", _Rooms.at(i)->SetOrGet_OpenDoor(1, 4, 0));

    }

    return;
}

#include <algorithm>
#include <iostream>
#include <memory>
#include "Core/RoomPatterns/RoomPatterns.h"
#include "Core/Library/DebugLib/DebugLib.h"
using namespace std;


/*
 * Pattern 1:
 * Cells:
 *      Cell 1:
 *            _Cells[0][0] - Coordinates
 *            _Cells[0][1] - Open/close door 1
 *            _Cells[0][2] - Open/close door 2
 *            _Cells[0][3] - Open/close door 3
 *            _Cells[0][4] - Open/close door 4
 */

RoomPattern_1::RoomPattern_1(INT SerialNumber)
{   
    DebugPrintMessange(INFO, "Creating room... \n");
    *_Pattern = 1;
    *_Class = 0;
    *_SerialNumber = SerialNumber;
    _Cells.resize(1);
    _Cells.at(0).assign(5, 0);
}

RoomPattern_1::~RoomPattern_1()
{
    DebugPrintMessange(INFO, "Destruction room... \n");
    _Cells.at(0).clear();
    _Cells.at(0).shrink_to_fit();
    _Cells.clear();
    _Cells.shrink_to_fit();
    delete _SerialNumber;
    delete _Pattern;
    delete _Class;
}

DOUBLE
RoomPattern_1::SetOrGet_RoomCellCoordinates(INT SetOrGet,
                                            INT DoorNumber,
                                            DOUBLE Coordinates)
{
    /*
     * The method will return the coordinates of cells with doors (by door number) or write coordinates to cells (to an available cell or by door number)
     * If 0 is passed in the DoorNumber argument, then the method will automatically select a free cell and write the coordinates into it (the choice can fall on any unoccupied cells, except for those with doors).
     * If you want to write the coordinates to a cell with a door - specify the door number in DoorNumber
    */

    if(SetOrGet == SET)
    {
        //This pattern does not allow automatic filling of cells without a door number (it does not contain cells without doors)

        if(DoorNumber != 0)
        {
            _Cells.at(0).at(0) = Coordinates;
        }
    }

    else if(SetOrGet == GET)
    {   
        if(DoorNumber != 0)
        {
            return _Cells.at(0).at(0);
        }
    }

    return 0;
}

INT
RoomPattern_1::Get_Pattern()
{
    return *_Pattern;
}

INT
RoomPattern_1::SetOrGet_RoomClass(INT SetOrGet,
                                  INT Class)
{
    if(SetOrGet == SET)
    {
        *_Class = Class;
    }
    else if(SetOrGet == GET)
    {
        return *_Class;
    }

    return 0;
}

INT
RoomPattern_1::SetOrGet_OpenDoor(INT SetOrGet,
                                 INT DoorNumber,
                                 INT DoorState)
{
    if(SetOrGet == SET)
    {
        _Cells.at(0).at(DoorNumber) = DoorState;
    }

    else if(SetOrGet == GET)
    {
        return _Cells.at(0).at(DoorNumber);
    }

    return 0;
}

vector<INT>
RoomPattern_1::Get_FreeDirections()
{
    vector<INT> FreeDirections;

    for(INT i = 1; i < 5; i++)
    {
        if(_Cells.at(0).at(i) == 0)
        {
            FreeDirections.push_back(i);
        }
    }

    return FreeDirections;
}

vector<DOUBLE>
RoomPattern_1::Get_RoomCellsCoordinates()
{
    vector<DOUBLE> CellsCoordinates;
    CellsCoordinates.push_back(_Cells.at(0).at(0));
    return CellsCoordinates;
}

INT
RoomPattern_1::Get_SerialNumber()
{
    return *_SerialNumber;
}

/* Pattern 1 END */




/*
 * Pattern 2:
 * Cells:
 *      Cell 1:
 *            _Cells[0][0] - Coordinates
 *            _Cells[0][1] - Open/close door 1
 *            _Cells[0][2] - Open/close door 2
 *
 *      Cell 2:
 *            _Cells[1][0] - Coordinates
 *            _Cells[1][1] - Open/close door 3
 *            _Cells[1][2] - Open/close door 4
 */

RoomPattern_2::RoomPattern_2(INT SerialNumber)
{
    DebugPrintMessange(INFO, "Creating room... \n");
    *_Pattern = 2;
    *_Class = 0;
    *_SerialNumber = SerialNumber;
    _Cells.resize(2);
    _Cells.at(0).assign(3, 0);
    _Cells.at(1).assign(3, 0);
}

RoomPattern_2::~RoomPattern_2()
{
    DebugPrintMessange(INFO, "Destruction room... \n");
    for(INT i = 0; i < 2; i++)
    {
        _Cells.at(i).clear();
        _Cells.at(i).shrink_to_fit();
    }
    _Cells.clear();
    _Cells.shrink_to_fit();
    delete _SerialNumber;
    delete _Pattern;
    delete _Class;
}

DOUBLE
RoomPattern_2::SetOrGet_RoomCellCoordinates(INT SetOrGet,
                                            INT DoorNumber,
                                            DOUBLE Coordinates)
{
    /*
     * The method will return the coordinates of cells with doors (by door number) or write coordinates to cells (to an available cell or by door number)
     * If 0 is passed in the DoorNumber argument, then the method will automatically select a free cell and write the coordinates into it (the choice can fall on any unoccupied cells, except for those with doors).
     * If you want to write the coordinates to a cell with a door - specify the door number in DoorNumber
    */

    if(SetOrGet == SET)
    {
        //This pattern does not allow automatic filling of cells without a door number (it does not contain cells without doors)

        if(DoorNumber == DOOR_1 || DoorNumber == DOOR_2)
        {
            _Cells.at(0).at(0) = Coordinates;
        }

        else if(DoorNumber == DOOR_3 || DoorNumber == DOOR_4)
        {
            _Cells.at(1).at(0) = Coordinates;
        }
    }

    else if(SetOrGet == GET)
    {
        if(DoorNumber == DOOR_1 || DoorNumber == DOOR_2)
        {
            return _Cells.at(0).at(0);
        }

        else if(DoorNumber == DOOR_3 || DoorNumber == DOOR_4)
        {
            return _Cells.at(1).at(0);
        }
    }

    return 0;
}

INT
RoomPattern_2::Get_Pattern()
{
    return *_Pattern;
}

INT
RoomPattern_2::SetOrGet_RoomClass(INT SetOrGet,
                                  INT Class)
{
    if(SetOrGet == SET)
    {
        *_Class = Class;
    }

    else if(SetOrGet == GET)
    {
        return *_Class;
    }

    return 0;
}

INT
RoomPattern_2::SetOrGet_OpenDoor(INT SetOrGet,
                                 INT DoorNumber,
                                 INT DoorState)
{
    if(SetOrGet == SET)
    {
        if(DoorNumber == DOOR_1)
        {
            _Cells.at(0).at(1) = DoorState;
        }

        else if(DoorNumber == DOOR_2)
        {
            _Cells.at(0).at(2) = DoorState;
        }

        else if(DoorNumber == DOOR_3)
        {
            _Cells.at(1).at(1) = DoorState;
        }

        else if(DoorNumber == DOOR_4)
        {
            _Cells.at(1).at(2) = DoorState;
        }
    }

    else if(SetOrGet == GET)
    {
        if(DoorNumber == DOOR_1)
        {
            return _Cells.at(0).at(1);
        }

        else if(DoorNumber == DOOR_2)
        {
            return _Cells.at(0).at(2);
        }

        else if(DoorNumber == DOOR_3)
        {
            return _Cells.at(1).at(1);
        }

        else if(DoorNumber == DOOR_4)
        {
            return _Cells.at(1).at(2);
        }
    }

    return 0;
}

vector<INT>
RoomPattern_2::Get_FreeDirections()
{
    /*
     * This method will help you get all free referrals (all closed door referrals).
    */

    vector<INT> FreeDirections;

    if(_Cells.at(0).at(1) == 0)
    {
        FreeDirections.push_back(1);
    }
    if(_Cells.at(0).at(2) == 0)
    {
        FreeDirections.push_back(2);
    }
    if(_Cells.at(1).at(1) == 0)
    {
        FreeDirections.push_back(3);
    }
    if(_Cells.at(1).at(2) == 0)
    {
        FreeDirections.push_back(4);
    }

    return FreeDirections;
}

vector<DOUBLE>
RoomPattern_2::Get_RoomCellsCoordinates()
{
    vector<DOUBLE> CellsCoordinates;

    for(INT i = 0; i < 2; i++)
    {
        CellsCoordinates.push_back(_Cells.at(i).at(0));
    }

    return CellsCoordinates;
}

INT
RoomPattern_2::Get_SerialNumber()
{
    return *_SerialNumber;
}

/* Pattern 2 END */




/*
 * Pattern 3:
 * Cells:
 *      Cell 1:
 *            _Cells[0][0] - Coordinates
 *            _Cells[0][1] - Open/close door 1
 *            _Cells[0][2] - Open/close door 4
 *
 *      Cell 2:
 *            _Cells[1][0] - Coordinates
 *            _Cells[1][1] - Open/close door 2
 *            _Cells[1][2] - Open/close door 3
 */

RoomPattern_3::RoomPattern_3(INT SerialNumber)
{
    DebugPrintMessange(INFO, "Creating room... \n");
    *_Pattern = 3;
    *_Class = 0;
    *_SerialNumber = SerialNumber;
    _Cells.resize(2);
    _Cells.at(0).assign(3, 0);
    _Cells.at(1).assign(3, 0);
}

RoomPattern_3::~RoomPattern_3()
{
    DebugPrintMessange(INFO, "Destruction room... \n");
    for(INT i = 0; i < 2; i++)
    {
        _Cells.at(i).clear();
        _Cells.at(i).shrink_to_fit();
    }
    _Cells.clear();
    _Cells.shrink_to_fit();
    delete _SerialNumber;
    delete _Pattern;
    delete _Class;
}

DOUBLE
RoomPattern_3::SetOrGet_RoomCellCoordinates(INT SetOrGet,
                                            INT DoorNumber,
                                            DOUBLE Coordinates)
{
    /*
     * The method will return the coordinates of cells with doors (by door number) or write coordinates to cells (to an available cell or by door number)
     * If 0 is passed in the DoorNumber argument, then the method will automatically select a free cell and write the coordinates into it (the choice can fall on any unoccupied cells, except for those with doors).
     * If you want to write the coordinates to a cell with a door - specify the door number in DoorNumber
    */

    if(SetOrGet == SET)
    {
        //This pattern does not allow automatic filling of cells without a door number (it does not contain cells without doors)

        if(DoorNumber == DOOR_1 || DoorNumber == DOOR_4)
        {
            _Cells.at(0).at(0) = Coordinates;
        }

        else if(DoorNumber == DOOR_2 || DoorNumber == DOOR_3)
        {
            _Cells.at(1).at(0) = Coordinates;
        }
    }

    else if(SetOrGet == GET)
    {
        if(DoorNumber == DOOR_1 || DoorNumber == DOOR_4)
        {
            return _Cells.at(0).at(0);
        }

        else if(DoorNumber == DOOR_2 || DoorNumber == DOOR_3)
        {
            return _Cells.at(1).at(0);
        }
    }

    return 0;
}

INT
RoomPattern_3::Get_Pattern()
{
    return *_Pattern;
}

INT
RoomPattern_3::SetOrGet_RoomClass(INT SetOrGet,
                                  INT Class)
{
    if(SetOrGet == SET)
    {
        *_Class = Class;
    }

    else if(SetOrGet == GET)
    {
        return *_Class;
    }

    return 0;
}

INT
RoomPattern_3::SetOrGet_OpenDoor(INT SetOrGet,
                                 INT DoorNumber,
                                 INT DoorState)
{
    if(SetOrGet == SET)
    {
        if(DoorNumber == DOOR_1)
        {
            _Cells.at(0).at(1) = DoorState;
        }

        else if(DoorNumber == DOOR_2)
        {
            _Cells.at(1).at(1) = DoorState;
        }

        else if(DoorNumber == DOOR_3)
        {
            _Cells.at(1).at(2) = DoorState;
        }

        else if(DoorNumber == DOOR_4)
        {
            _Cells.at(0).at(2) = DoorState;
        }
    }

    else if(SetOrGet == GET)
    {
        if(DoorNumber == DOOR_1)
        {
            return _Cells.at(0).at(1);
        }

        else if(DoorNumber == DOOR_2)
        {
            return _Cells.at(1).at(1);
        }

        else if(DoorNumber == DOOR_3)
        {
            return _Cells.at(1).at(2);
        }

        else if(DoorNumber == DOOR_4)
        {
            return _Cells.at(0).at(2);
        }
    }

    return 0;
}

vector<INT>
RoomPattern_3::Get_FreeDirections()
{
    /*
     * This method will help you get all free referrals (all closed door referrals).
    */

    vector<INT> FreeDirections;

    if(_Cells.at(0).at(1) == 0)
    {
        FreeDirections.push_back(1);
    }
    if(_Cells.at(1).at(1) == 0)
    {
        FreeDirections.push_back(2);
    }
    if(_Cells.at(1).at(2) == 0)
    {
        FreeDirections.push_back(3);
    }
    if(_Cells.at(0).at(2) == 0)
    {
        FreeDirections.push_back(4);
    }

    return FreeDirections;
}

vector<DOUBLE>
RoomPattern_3::Get_RoomCellsCoordinates()
{
    vector<DOUBLE> CellsCoordinates;

    for(INT i = 0; i < 2; i++)
    {
        CellsCoordinates.push_back(_Cells.at(i).at(0));
    }

    return CellsCoordinates;
}

INT
RoomPattern_3::Get_SerialNumber()
{
    return *_SerialNumber;
}

/* Pattern 3 END */




/*
 * Pattern 4:
 * Cells:
 *      Cell 1:
 *            _Cells[0][0] - Coordinates
 *            _Cells[0][1] - Open/close door 1
 *            _Cells[0][2] - Open/close door 2
 *
 *      Cell 2:
 *            _Cells[1][0] - Coordinates
 *
 *      Cell 3:
 *            _Cells[2][0] - Coordinates
 *            _Cells[2][1] - Open/close door 3
 *            _Cells[2][2] - Open/close door 4
 */

RoomPattern_4::RoomPattern_4(INT SerialNumber)
{
    DebugPrintMessange(INFO, "Creating room... \n");
    *_Pattern = 4;
    *_Class = 0;
    *_SerialNumber = SerialNumber;
    _Cells.resize(3);
    _Cells.at(0).assign(3, 0);
    _Cells.at(1).assign(1, 0);
    _Cells.at(2).assign(3, 0);
}

RoomPattern_4::~RoomPattern_4()
{
    DebugPrintMessange(INFO, "Destruction room... \n");
    for(INT i = 0; i < 3; i++)
    {
        _Cells.at(i).clear();
        _Cells.at(i).shrink_to_fit();
    }
    _Cells.clear();
    _Cells.shrink_to_fit();
    delete _SerialNumber;
    delete _Pattern;
    delete _Class;
}

DOUBLE
RoomPattern_4::SetOrGet_RoomCellCoordinates(INT SetOrGet,
                                            INT DoorNumber,
                                            DOUBLE Coordinates)
{
    /*
     * The method will return the coordinates of cells with doors (by door number) or write coordinates to cells (to an available cell or by door number)
     * If 0 is passed in the DoorNumber argument, then the method will automatically select a free cell and write the coordinates into it (the choice can fall on any unoccupied cells, except for those with doors).
     * If you want to write the coordinates to a cell with a door - specify the door number in DoorNumber
    */

    if(SetOrGet == SET)
    {
        if(DoorNumber == 0)
        {
            _Cells.at(1).at(0) = Coordinates;
        }

        else if(DoorNumber == DOOR_1 || DoorNumber == DOOR_2)
        {
            _Cells.at(0).at(0) = Coordinates;
        }

        else if(DoorNumber == DOOR_3 || DoorNumber == DOOR_4)
        {
            _Cells.at(2).at(0) = Coordinates;
        }
    }

    else if(SetOrGet == GET)
    {
        if(DoorNumber == DOOR_1 || DoorNumber == DOOR_2)
        {
            return _Cells.at(0).at(0);
        }

        else if(DoorNumber == DOOR_3 || DoorNumber == DOOR_4)
        {
            return _Cells.at(2).at(0);
        }
    }

    return 0;
}

INT
RoomPattern_4::Get_Pattern()
{
    return *_Pattern;
}

INT
RoomPattern_4::SetOrGet_RoomClass(INT SetOrGet,
                                  INT Class)
{
    if(SetOrGet == SET)
    {
        *_Class = Class;
    }

    else if(SetOrGet == GET)
    {
        return *_Class;
    }

    return 0;
}

INT
RoomPattern_4::SetOrGet_OpenDoor(INT SetOrGet,
                                 INT DoorNumber,
                                 INT DoorState)
{
    if(SetOrGet == SET)
    {
        if(DoorNumber == DOOR_1)
        {
            _Cells.at(0).at(1) = DoorState;
        }

        else if(DoorNumber == DOOR_2)
        {
            _Cells.at(0).at(2) = DoorState;
        }

        else if(DoorNumber == DOOR_3)
        {
            _Cells.at(2).at(1) = DoorState;
        }

        else if(DoorNumber == DOOR_4)
        {
            _Cells.at(2).at(2) = DoorState;
        }
    }

    else if(SetOrGet == GET)
    {
        if(DoorNumber == DOOR_1)
        {
            return _Cells.at(0).at(1);
        }

        else if(DoorNumber == DOOR_2)
        {
            return _Cells.at(0).at(2);
        }

        else if(DoorNumber == DOOR_3)
        {
            return _Cells.at(2).at(1);
        }

        else if(DoorNumber == DOOR_4)
        {
            return _Cells.at(2).at(2);
        }
    }

    return 0;
}

vector<INT>
RoomPattern_4::Get_FreeDirections()
{
    /*
     * This method will help you get all free referrals (all closed door referrals).
    */

    vector<INT> FreeDirections;

    if(_Cells.at(0).at(1) == 0)
    {
        FreeDirections.push_back(1);
    }
    if(_Cells.at(0).at(2) == 0)
    {
        FreeDirections.push_back(2);
    }
    if(_Cells.at(2).at(1) == 0)
    {
        FreeDirections.push_back(3);
    }
    if(_Cells.at(2).at(2) == 0)
    {
        FreeDirections.push_back(4);
    }

    return FreeDirections;
}

vector<DOUBLE>
RoomPattern_4::Get_RoomCellsCoordinates()
{
    vector<DOUBLE> CellsCoordinates;
    for(INT i = 0; i < 3; i++)
    {
        CellsCoordinates.push_back(_Cells.at(i).at(0));
    }
    return CellsCoordinates;
}

INT
RoomPattern_4::Get_SerialNumber()
{
    return *_SerialNumber;
}

/* Pattern 4 END */




/*
 * Pattern 5:
 * Cells:
 *      Cell 1:
 *            _Cells[0][0] - Coordinates
 *            _Cells[0][1] - Open/close door 1
 *            _Cells[0][2] - Open/close door 4
 *
 *      Cell 2:
 *            _Cells[1][0] - Coordinates
 *
 *      Cell 3:
 *            _Cells[2][0] - Coordinates
 *            _Cells[2][1] - Open/close door 2
 *            _Cells[2][2] - Open/close door 3
 */

RoomPattern_5::RoomPattern_5(INT SerialNumber)
{
    DebugPrintMessange(INFO, "Creating room... \n");
    *_Pattern = 5;
    *_Class = 0;
    *_SerialNumber = SerialNumber;
    _Cells.resize(3);
    _Cells.at(0).assign(3, 0);
    _Cells.at(1).assign(1, 0);
    _Cells.at(2).assign(3, 0);
}

RoomPattern_5::~RoomPattern_5()
{
    DebugPrintMessange(INFO, "Destruction room... \n");
    for(INT i = 0; i < 3; i++)
    {
        _Cells.at(i).clear();
        _Cells.at(i).shrink_to_fit();
    }
    _Cells.clear();
    _Cells.shrink_to_fit();
    delete _SerialNumber;
    delete _Pattern;
    delete _Class;
}

DOUBLE
RoomPattern_5::SetOrGet_RoomCellCoordinates(INT SetOrGet,
                                            INT DoorNumber,
                                            DOUBLE Coordinates)
{
    /*
     * The method will return the coordinates of cells with doors (by door number) or write coordinates to cells (to an available cell or by door number)
     * If 0 is passed in the DoorNumber argument, then the method will automatically select a free cell and write the coordinates into it (the choice can fall on any unoccupied cells, except for those with doors).
     * If you want to write the coordinates to a cell with a door - specify the door number in DoorNumber
    */

    if(SetOrGet == SET)
    {
        if(DoorNumber == 0)
        {
            _Cells.at(1).at(0) = Coordinates;
        }

        else if(DoorNumber == DOOR_1 || DoorNumber == DOOR_4)
        {
            _Cells.at(0).at(0) = Coordinates;
        }

        else if(DoorNumber == DOOR_2 || DoorNumber == DOOR_3)
        {
            _Cells.at(2).at(0) = Coordinates;
        }
    }

    else if(SetOrGet == GET)
    {
        if(DoorNumber == DOOR_1 || DoorNumber == DOOR_4)
        {
            return _Cells.at(0).at(0);
        }

        else if(DoorNumber == DOOR_2 || DoorNumber == DOOR_3)
        {
            return _Cells.at(2).at(0);
        }
    }

    return 0;
}

INT
RoomPattern_5::Get_Pattern()
{
    return *_Pattern;
}

INT
RoomPattern_5::SetOrGet_RoomClass(INT SetOrGet,
                                  INT Class)
{
    if(SetOrGet == SET)
    {
        *_Class = Class;
    }

    else if(SetOrGet == GET)
    {
        return *_Class;
    }

    return 0;
}

INT
RoomPattern_5::SetOrGet_OpenDoor(INT SetOrGet,
                                 INT DoorNumber,
                                 INT DoorState)
{
    if(SetOrGet == SET)
    {
        if(DoorNumber == DOOR_1)
        {
            _Cells.at(0).at(1) = DoorState;
        }

        else if(DoorNumber == DOOR_2)
        {
            _Cells.at(2).at(1) = DoorState;
        }

        else if(DoorNumber == DOOR_3)
        {
            _Cells.at(2).at(2) = DoorState;
        }

        else if(DoorNumber == DOOR_4)
        {
            _Cells.at(0).at(2) = DoorState;
        }
    }

    else if(SetOrGet == GET)
    {
        if(DoorNumber == DOOR_1)
        {
            return _Cells.at(0).at(1);
        }

        else if(DoorNumber == DOOR_2)
        {
            return _Cells.at(2).at(1);
        }

        else if(DoorNumber == DOOR_3)
        {
            return _Cells.at(2).at(2);
        }

        else if(DoorNumber == DOOR_4)
        {
            return _Cells.at(0).at(2);
        }
    }

    return 0;
}

vector<INT>
RoomPattern_5::Get_FreeDirections()
{
    /*
     * This method will help you get all free referrals (all closed door referrals).
    */

    vector<int> FreeDirections;

    if(_Cells.at(0).at(1) == 0)
    {
        FreeDirections.push_back(1);
    }
    if(_Cells.at(2).at(1) == 0)
    {
        FreeDirections.push_back(2);
    }
    if(_Cells.at(2).at(2) == 0)
    {
        FreeDirections.push_back(3);
    }
    if(_Cells.at(0).at(2) == 0)
    {
        FreeDirections.push_back(4);
    }

    return FreeDirections;
}

vector<DOUBLE>
RoomPattern_5::Get_RoomCellsCoordinates()
{
    vector<DOUBLE> CellsCoordinates;
    for(INT i = 0; i < 3; i++)
    {
        CellsCoordinates.push_back(_Cells.at(i).at(0));
    }
    return CellsCoordinates;
}

INT
RoomPattern_5::Get_SerialNumber()
{
    return *_SerialNumber;
}

/* Pattern 5 END */




/*
 * Pattern 6:
 * Cells:
 *      Cell 1:
 *            _Cells[0][0] - Coordinates
 *            _Cells[0][1] - Open/close door 1
 *            _Cells[0][2] - Open/close door 4
 *
 *      Cell 2:
 *            _Cells[1][0] - Coordinates
 *
 *      Cell 3:
 *            _Cells[2][0] - Coordinates
 *            _Cells[2][1] - Open/close door 2
 *            _Cells[2][2] - Open/close door 3
 */

RoomPattern_6::RoomPattern_6(INT SerialNumber)
{
    DebugPrintMessange(INFO, "Creating room... \n");
    *_Pattern = 6;
    *_Class = 0;
    *_SerialNumber = SerialNumber;
    _Cells.resize(3);
    _Cells.at(0).assign(3, 0);
    _Cells.at(1).assign(1, 0);
    _Cells.at(2).assign(3, 0);
}

RoomPattern_6::~RoomPattern_6()
{
    DebugPrintMessange(INFO, "Destruction room... \n");
    for(INT i = 0; i < 3; i++)
    {
        _Cells.at(i).clear();
        _Cells.at(i).shrink_to_fit();
    }
    _Cells.clear();
    _Cells.shrink_to_fit();
    delete _SerialNumber;
    delete _Pattern;
    delete _Class;
}

DOUBLE
RoomPattern_6::SetOrGet_RoomCellCoordinates(INT SetOrGet,
                                            INT DoorNumber,
                                            DOUBLE Coordinates)
{
    /*
     * The method will return the coordinates of cells with doors (by door number) or write coordinates to cells (to an available cell or by door number)
     * If 0 is passed in the DoorNumber argument, then the method will automatically select a free cell and write the coordinates into it (the choice can fall on any unoccupied cells, except for those with doors).
     * If you want to write the coordinates to a cell with a door - specify the door number in DoorNumber
    */

    if(SetOrGet == SET)
    {
        if(DoorNumber == 0)
        {
            _Cells.at(1).at(0) = Coordinates;
        }

        else if(DoorNumber == DOOR_1 || DoorNumber == DOOR_4)
        {
            _Cells.at(0).at(0) = Coordinates;
        }

        else if(DoorNumber == DOOR_2 || DoorNumber == DOOR_3)
        {
            _Cells.at(2).at(0) = Coordinates;
        }
    }

    else if(SetOrGet == GET)
    {
        if(DoorNumber == DOOR_1 || DoorNumber == DOOR_4)
        {
            return _Cells.at(0).at(0);
        }

        else if(DoorNumber == DOOR_2 || DoorNumber == DOOR_3)
        {
            return _Cells.at(2).at(0);
        }
    }

    return 0;
}

INT
RoomPattern_6::Get_Pattern()
{
    return *_Pattern;
}

INT
RoomPattern_6::SetOrGet_RoomClass(INT SetOrGet,
                                  INT Class)
{
    if(SetOrGet == SET)
    {
        *_Class = Class;
    }

    else if(SetOrGet == GET)
    {
        return *_Class;
    }

    return 0;
}

INT
RoomPattern_6::SetOrGet_OpenDoor(INT SetOrGet,
                                 INT DoorNumber,
                                 INT DoorState)
{
    if(SetOrGet == SET)
    {
        if(DoorNumber == DOOR_1)
        {
            _Cells.at(0).at(1) = DoorState;
        }

        else if(DoorNumber == DOOR_2)
        {
            _Cells.at(2).at(1) = DoorState;
        }

        else if(DoorNumber == DOOR_3)
        {
            _Cells.at(2).at(2) = DoorState;
        }

        else if(DoorNumber == DOOR_4)
        {
            _Cells.at(0).at(2) = DoorState;
        }
    }

    else if(SetOrGet == GET)
    {
        if(DoorNumber == DOOR_1)
        {
            return _Cells.at(0).at(1);
        }

        else if(DoorNumber == DOOR_2)
        {
            return _Cells.at(2).at(1);
        }

        else if(DoorNumber == DOOR_3)
        {
            return _Cells.at(2).at(2);
        }

        else if(DoorNumber == DOOR_4)
        {
            return _Cells.at(0).at(2);
        }
    }

    return 0;
}

vector<INT>
RoomPattern_6::Get_FreeDirections()
{
    /*
     * This method will help you get all free referrals (all closed door referrals).
    */

    vector<INT> FreeDirections;

    if(_Cells.at(0).at(1) == 0)
    {
        FreeDirections.push_back(1);
    }
    if(_Cells.at(2).at(1) == 0)
    {
        FreeDirections.push_back(2);
    }
    if(_Cells.at(2).at(2) == 0)
    {
        FreeDirections.push_back(3);
    }
    if(_Cells.at(0).at(2) == 0)
    {
        FreeDirections.push_back(4);
    }

    return FreeDirections;
}

vector<DOUBLE>
RoomPattern_6::Get_RoomCellsCoordinates()
{
    vector<DOUBLE> CellsCoordinates;
    for(INT i = 0; i < 3; i++)
    {
        CellsCoordinates.push_back(_Cells.at(i).at(0));
    }
    return CellsCoordinates;
}

INT
RoomPattern_6::Get_SerialNumber()
{
    return *_SerialNumber;
}

/* Pattern 6 END */




/*
 * Pattern 7:
 * Cells:
 *      Cell 1:
 *            _Cells[0][0] - Coordinates
 *            _Cells[0][1] - Open/close door 1
 *            _Cells[0][2] - Open/close door 2
 *
 *      Cell 2:
 *            _Cells[1][0] - Coordinates
 *
 *      Cell 3:
 *            _Cells[2][0] - Coordinates
 *            _Cells[2][1] - Open/close door 3
 *            _Cells[2][2] - Open/close door 4
 */

RoomPattern_7::RoomPattern_7(INT SerialNumber)
{
    DebugPrintMessange(INFO, "Creating room... \n");
    *_Pattern = 7;
    *_Class = 0;
    *_SerialNumber = SerialNumber;
    _Cells.resize(3);
    _Cells.at(0).assign(3, 0);
    _Cells.at(1).assign(1, 0);
    _Cells.at(2).assign(3, 0);
}

RoomPattern_7::~RoomPattern_7()
{
    DebugPrintMessange(INFO, "Destruction room... \n");
    for(INT i = 0; i < 3; i++)
    {
        _Cells.at(i).clear();
        _Cells.at(i).shrink_to_fit();
    }
    _Cells.clear();
    _Cells.shrink_to_fit();
    delete _SerialNumber;
    delete _Pattern;
    delete _Class;
}

DOUBLE
RoomPattern_7::SetOrGet_RoomCellCoordinates(INT SetOrGet,
                                            INT DoorNumber,
                                            DOUBLE Coordinates)
{
    /*
     * The method will return the coordinates of cells with doors (by door number) or write coordinates to cells (to an available cell or by door number)
     * If 0 is passed in the DoorNumber argument, then the method will automatically select a free cell and write the coordinates into it (the choice can fall on any unoccupied cells, except for those with doors).
     * If you want to write the coordinates to a cell with a door - specify the door number in DoorNumber
    */

    if(SetOrGet == SET)
    {
        if(DoorNumber == 0)
        {
            _Cells.at(1).at(0) = Coordinates;
        }

        else if(DoorNumber == DOOR_1 || DoorNumber == DOOR_2)
        {
            _Cells.at(0).at(0) = Coordinates;
        }

        else if(DoorNumber == DOOR_3 || DoorNumber == DOOR_4)
        {
            _Cells.at(2).at(0) = Coordinates;
        }
    }

    else if(SetOrGet == GET)
    {
        if(DoorNumber == DOOR_1 || DoorNumber == DOOR_2)
        {
            return _Cells.at(0).at(0);
        }

        else if(DoorNumber == DOOR_3 || DoorNumber == DOOR_4)
        {
            return _Cells.at(2).at(0);
        }
    }

    return 0;
}

INT
RoomPattern_7::Get_Pattern()
{
    return *_Pattern;
}

INT
RoomPattern_7::SetOrGet_RoomClass(INT SetOrGet,
                                  INT Class)
{
    if(SetOrGet == 0)
    {
        *_Class = Class;
    }

    else if(SetOrGet == 1)
    {
        return *_Class;
    }

    return 0;
}

INT
RoomPattern_7::SetOrGet_OpenDoor(INT SetOrGet,
                                 INT DoorNumber,
                                 INT DoorState)
{  
    if(SetOrGet == SET)
    {
        if(DoorNumber == DOOR_1)
        {
            _Cells.at(0).at(1) = DoorState;
        }

        else if(DoorNumber == DOOR_2)
        {
            _Cells.at(0).at(2) = DoorState;
        }

        else if(DoorNumber == DOOR_3)
        {
            _Cells.at(2).at(1) = DoorState;
        }

        else if(DoorNumber == DOOR_4)
        {
            _Cells.at(2).at(2) = DoorState;
        }
    }

    else if(SetOrGet == GET)
    {
        if(DoorNumber == DOOR_1)
        {
            return _Cells.at(0).at(1);
        }

        else if(DoorNumber == DOOR_2)
        {
            return _Cells.at(0).at(2);
        }

        else if(DoorNumber == DOOR_3)
        {
            return _Cells.at(2).at(1);
        }

        else if(DoorNumber == DOOR_4)
        {
            return _Cells.at(2).at(2);
        }
    }

    return 0;
}

vector<INT>
RoomPattern_7::Get_FreeDirections()
{
    /*
     * This method will help you get all free referrals (all closed door referrals).
    */

    vector<INT> FreeDirections;

    if(_Cells.at(0).at(1) == 0)
    {
        FreeDirections.push_back(1);
    }
    if(_Cells.at(0).at(2) == 0)
    {
        FreeDirections.push_back(2);
    }
    if(_Cells.at(2).at(1) == 0)
    {
        FreeDirections.push_back(3);
    }
    if(_Cells.at(2).at(2) == 0)
    {
        FreeDirections.push_back(4);
    }

    return FreeDirections;
}

vector<DOUBLE>
RoomPattern_7::Get_RoomCellsCoordinates()
{
    vector<DOUBLE> CellsCoordinates;
    for(INT i = 0; i < 3; i++)
    {
        CellsCoordinates.push_back(_Cells.at(i).at(0));
    }
    return CellsCoordinates;
}

INT
RoomPattern_7::Get_SerialNumber()
{
    return *_SerialNumber;
}

/* Pattern 7 END */




/*
 * Pattern 8:
 * Cells:
 *      Cell 1:
 *            _Cells[0][0] - Coordinates
 *            _Cells[0][1] - Open/close door 1
 *
 *      Cell 2:
 *            _Cells[1][0] - Coordinates
 *            _Cells[1][1] - Open/close door 2
 *
 *      Cell 3:
 *            _Cells[2][0] - Coordinates
 *            _Cells[2][1] - Open/close door 3
 *
 *      Cell 4:
 *            _Cells[3][0] - Coordinates
 *            _Cells[3][1] - Open/close door 4
 */

RoomPattern_8::RoomPattern_8(INT SerialNumber)
{
    DebugPrintMessange(INFO, "Creating room... \n");
    *_Pattern = 8;
    *_Class = 0;
    *_SerialNumber = SerialNumber;
    _Cells.resize(4);
    _Cells.at(0).assign(2, 0);
    _Cells.at(1).assign(2, 0);
    _Cells.at(2).assign(2, 0);
    _Cells.at(3).assign(2, 0);
}

RoomPattern_8::~RoomPattern_8()
{
    DebugPrintMessange(INFO, "Destruction room... \n");
    for(INT i = 0; i < 4; i++)
    {
        _Cells.at(i).clear();
        _Cells.at(i).shrink_to_fit();
    }
    _Cells.clear();
    _Cells.shrink_to_fit();
    delete _SerialNumber;
    delete _Pattern;
    delete _Class;
}

DOUBLE
RoomPattern_8::SetOrGet_RoomCellCoordinates(INT SetOrGet,
                                            INT DoorNumber,
                                            DOUBLE Coordinates)
{
    /*
     * The method will return the coordinates of cells with doors (by door number) or write coordinates to cells (to an available cell or by door number)
     * If 0 is passed in the DoorNumber argument, then the method will automatically select a free cell and write the coordinates into it (the choice can fall on any unoccupied cells, except for those with doors).
     * If you want to write the coordinates to a cell with a door - specify the door number in DoorNumber
    */

    if(SetOrGet == SET)
    {
        _Cells.at(DoorNumber - 1).at(0) = Coordinates;
    }

    else if(SetOrGet == GET)
    {
        return _Cells.at(DoorNumber - 1).at(0);
    }

    return 0;
}

INT
RoomPattern_8::Get_Pattern()
{
    return *_Pattern;
}

INT
RoomPattern_8::SetOrGet_RoomClass(INT SetOrGet,
                                  INT Class)
{
    if(SetOrGet == 0)
    {
        *_Class = Class;
    }

    else if(SetOrGet == 1)
    {
        return *_Class;
    }

    return 0;
}

INT
RoomPattern_8::SetOrGet_OpenDoor(INT SetOrGet,
                                 INT DoorNumber,
                                 INT DoorState)
{
    if(SetOrGet == SET)
    {
        _Cells.at(DoorNumber - 1).at(1) = DoorState;
    }

    else if(SetOrGet == GET)
    {
        return _Cells.at(DoorNumber - 1).at(1);
    }

    return 0;
}

vector<INT>
RoomPattern_8::Get_FreeDirections()
{
    /*
     * This method will help you get all free referrals (all closed door referrals).
    */

    vector<INT> FreeDirections;

    if(_Cells.at(0).at(1) == 0)
    {
        FreeDirections.push_back(1);
    }
    if(_Cells.at(1).at(1) == 0)
    {
        FreeDirections.push_back(2);
    }
    if(_Cells.at(2).at(1) == 0)
    {
        FreeDirections.push_back(3);
    }
    if(_Cells.at(3).at(1) == 0)
    {
        FreeDirections.push_back(4);
    }

    return FreeDirections;
}

vector<DOUBLE>
RoomPattern_8::Get_RoomCellsCoordinates()
{
    vector<DOUBLE> CellsCoordinates;
    for(INT i = 0; i < 4; i++)
    {
        CellsCoordinates.push_back(_Cells.at(i).at(0));
    }
    return CellsCoordinates;
}

INT
RoomPattern_8::Get_SerialNumber()
{
    return *_SerialNumber;
}

/* Pattern 8 END */

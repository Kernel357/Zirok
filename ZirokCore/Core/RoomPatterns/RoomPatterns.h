#ifndef _ROOM_PATTERNS_H
#define _ROOM_PATTERNS_H

#include "Core/RoomPatterns/BaseRoomPattern.h"

class RoomPattern_1 : public BaseRoomPattern{
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

private:
    vector<vector<DOUBLE>> _Cells;          // The vector contains information about the room cell (coordinates, door status).
    INT *_Pattern = new INT();              // Contains room pattern.
    INT *_Class = new INT();                // Contains room class.
    INT *_SerialNumber = new INT();         // Contains the serial number of the room.

public:
    RoomPattern_1(INT SerialNumber);
    ~RoomPattern_1();

    DOUBLE
    SetOrGet_RoomCellCoordinates(INT SetOrGet,
                                 INT DoorNumber,
                                 DOUBLE Coordinates);

    INT
    Get_Pattern();

    INT
    SetOrGet_RoomClass(INT SetOrGet,
                       INT Class);

    INT
    SetOrGet_OpenDoor(INT SetOrGet,
                      INT DoorNumber,
                      INT DoorState);

    vector<INT>
    Get_FreeDirections();

    vector<DOUBLE>
    Get_RoomCellsCoordinates();

    INT
    Get_SerialNumber();
};


class RoomPattern_2 : public BaseRoomPattern{
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

private:
    vector<vector<DOUBLE>> _Cells;          // The vector contains information about the room cell (coordinates, door status).
    INT *_Pattern = new INT();              // Contains room pattern.
    INT *_Class = new INT();                // Contains room class.
    INT *_SerialNumber = new INT();         // Contains the serial number of the room.

public:
    RoomPattern_2(INT SerialNumber);
    ~RoomPattern_2();

    DOUBLE
    SetOrGet_RoomCellCoordinates(INT SetOrGet,
                                 INT DoorNumber,
                                 DOUBLE Coordinates);

    INT
    Get_Pattern();

    INT
    SetOrGet_RoomClass(INT SetOrGet,
                       INT Class);

    INT
    SetOrGet_OpenDoor(INT SetOrGet,
                      INT DoorNumber,
                      INT DoorState);

    vector<INT>
    Get_FreeDirections();

    vector<DOUBLE>
    Get_RoomCellsCoordinates();

    INT
    Get_SerialNumber();
};


class RoomPattern_3 : public BaseRoomPattern{
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

private:
    vector<vector<DOUBLE>> _Cells;          // The vector contains information about the room cell (coordinates, door status).
    INT *_Pattern = new INT();              // Contains room pattern.
    INT *_Class = new INT();                // Contains room class.
    INT *_SerialNumber = new INT();         // Contains the serial number of the room.

public:
    RoomPattern_3(INT SerialNumber);
    ~RoomPattern_3();

    DOUBLE
    SetOrGet_RoomCellCoordinates(INT SetOrGet,
                                 INT DoorNumber,
                                 DOUBLE Coordinates);

    INT
    Get_Pattern();

    INT
    SetOrGet_RoomClass(INT SetOrGet,
                       INT Class);

    INT
    SetOrGet_OpenDoor(INT SetOrGet,
                      INT DoorNumber,
                      INT DoorState);

    vector<INT>
    Get_FreeDirections();

    vector<DOUBLE>
    Get_RoomCellsCoordinates();

    INT
    Get_SerialNumber();
};


class RoomPattern_4 : public BaseRoomPattern{
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

private:
    vector<vector<DOUBLE>> _Cells;          // The vector contains information about the room cell (coordinates, door status).
    INT *_Pattern = new INT();              // Contains room pattern.
    INT *_Class = new INT();                // Contains room class.
    INT *_SerialNumber = new INT();         // Contains the serial number of the room.

public:
    RoomPattern_4(INT SerialNumber);
    ~RoomPattern_4();

    DOUBLE
    SetOrGet_RoomCellCoordinates(INT SetOrGet,
                                 INT DoorNumber,
                                 DOUBLE Coordinates);

    INT
    Get_Pattern();

    INT
    SetOrGet_RoomClass(INT SetOrGet,
                       INT Class);

    INT
    SetOrGet_OpenDoor(INT SetOrGet,
                      INT DoorNumber,
                      INT DoorState);

    vector<INT>
    Get_FreeDirections();

    vector<DOUBLE>
    Get_RoomCellsCoordinates();

    INT
    Get_SerialNumber();
};


class RoomPattern_5 : public BaseRoomPattern{
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
     
private:
    vector<vector<DOUBLE>> _Cells;          // The vector contains information about the room cell (coordinates, door status).
    INT *_Pattern = new INT();              // Contains room pattern.
    INT *_Class = new INT();                // Contains room class.
    INT *_SerialNumber = new INT();         // Contains the serial number of the room.

public:
    RoomPattern_5(INT SerialNumber);
    ~RoomPattern_5();

    DOUBLE
    SetOrGet_RoomCellCoordinates(INT SetOrGet,
                                 INT DoorNumber,
                                 DOUBLE Coordinates);

    INT
    Get_Pattern();

    INT
    SetOrGet_RoomClass(INT SetOrGet,
                       INT Class);

    INT
    SetOrGet_OpenDoor(INT SetOrGet,
                      INT DoorNumber,
                      INT DoorState);

    vector<INT>
    Get_FreeDirections();

    vector<DOUBLE>
    Get_RoomCellsCoordinates();

    INT
    Get_SerialNumber();
};


class RoomPattern_6 : public BaseRoomPattern{
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

private:
    vector<vector<DOUBLE>> _Cells;          // The vector contains information about the room cell (coordinates, door status).
    INT *_Pattern = new INT();              // Contains room pattern.
    INT *_Class = new INT();                // Contains room class.
    INT *_SerialNumber = new INT();         // Contains the serial number of the room.

public:
    RoomPattern_6(INT SerialNumber);
    ~RoomPattern_6();

    DOUBLE
    SetOrGet_RoomCellCoordinates(INT SetOrGet,
                                 INT DoorNumber,
                                 DOUBLE Coordinates);

    INT
    Get_Pattern();

    INT
    SetOrGet_RoomClass(INT SetOrGet,
                           INT Class);

    INT
    SetOrGet_OpenDoor(INT SetOrGet,
                      INT DoorNumber,
                      INT DoorState);

    vector<INT>
    Get_FreeDirections();

    vector<DOUBLE>
    Get_RoomCellsCoordinates();

    INT
    Get_SerialNumber();
};


class RoomPattern_7 : public BaseRoomPattern{
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
private:
    vector<vector<DOUBLE>> _Cells;          // The vector contains information about the room cell (coordinates, door status).
    INT *_Pattern = new INT();              // Contains room pattern.
    INT *_Class = new INT();                // Contains room class.
    INT *_SerialNumber = new INT();         // Contains the serial number of the room.

public:
    RoomPattern_7(INT SerialNumber);
    ~RoomPattern_7();

    DOUBLE
    SetOrGet_RoomCellCoordinates(INT SetOrGet,
                                 INT DoorNumber,
                                 DOUBLE Coordinates);

    INT
    Get_Pattern();

    INT
    SetOrGet_RoomClass(INT SetOrGet,
                       INT Class);

    INT
    SetOrGet_OpenDoor(INT SetOrGet,
                      INT DoorNumber,
                      INT DoorState);

    vector<INT>
    Get_FreeDirections();

    vector<DOUBLE>
    Get_RoomCellsCoordinates();

    INT
    Get_SerialNumber();
};


class RoomPattern_8 : public BaseRoomPattern{
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

private:
    vector<vector<DOUBLE>> _Cells;          // The vector contains information about the room cell (coordinates, door status).
    INT *_Pattern = new INT();              // Contains room pattern.
    INT *_Class = new INT();                // Contains room class.
    INT *_SerialNumber = new INT();         // Contains the serial number of the room.

public:
    RoomPattern_8(INT SerialNumber);
    ~RoomPattern_8();

    DOUBLE
    SetOrGet_RoomCellCoordinates(INT SetOrGet,
                                 INT DoorNumber,
                                 DOUBLE Coordinates);

    INT
    Get_Pattern();

    INT
    SetOrGet_RoomClass(INT SetOrGet,
                       INT Class);

    INT
    SetOrGet_OpenDoor(INT SetOrGet,
                      INT DoorNumber,
                      INT DoorState);

    vector<INT>
    Get_FreeDirections();

    vector<DOUBLE>
    Get_RoomCellsCoordinates();

    INT
    Get_SerialNumber();
};

#endif

#include <vector>
#include "Core/BaseDef/BaseDef.h"

using namespace std;

class BaseRoomPattern{
public:
    virtual DOUBLE
    SetOrGet_RoomCellCoordinates(INT SetOrGet,
                                 INT DoorNumber,
                                 DOUBLE Coordinates) = 0;

    virtual INT
    Get_Pattern() = 0;

    virtual INT
    SetOrGet_RoomClass(INT SetOrGet,
                       INT Class) = 0;

    virtual INT
    SetOrGet_OpenDoor(INT SetOrGet,
                      INT DoorNumber,
                      INT IsOpen) = 0;

    virtual vector<INT>
    Get_FreeDirections() = 0;

    virtual vector<DOUBLE>
    Get_RoomCellsCoordinates() = 0;

    virtual INT
    Get_SerialNumber() = 0;

    virtual
    ~BaseRoomPattern() = default;
};

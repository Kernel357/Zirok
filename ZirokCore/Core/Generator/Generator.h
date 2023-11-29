#include <locale>
#include <memory>
#include <vector>
#include "Core/RoomPatterns/RoomPatterns.h"                         // Contains all patterns.
#include "Core/Library/RandomLib/RandomLib.h"                       // Library for random.
#include "Core/BaseDef/BaseDef.h"                                   // Contains all base defines.
#include "Core/Library/DebugLib/DebugLib.h"                         // Library for debugging.

using namespace std;

class Generator{
private:
    /*====================
      Core service fields
     ====================*/
    STATUS *_Status = new STATUS();                                 // Contains the status of the last operation.
    INT *_Direction = new INT();                                    // Contains the direction in which the next room will be generated.
    INT *_RandomRoom = new INT();                                   // Contains a randomly selected parent room.
    INT *_CurrentRoom = new INT();                                  // Contains the number of the currently generated room.
    INT *_ChildRoomPattern = new INT();                             // Contains the pattern of the next child room.
    INT *_CellIterator = new INT();                                 // Contains the number of free cells.

    /*=================
      Core conf fields
     =================*/
    vector<shared_ptr<BaseRoomPattern>>  _Rooms;                    // Vector with all rooms.
    vector<shared_ptr<BaseRoomPattern>>  _SortedParentRooms;        // Vector with sorted rooms for RandomLib.
    vector<DOUBLE> _OccupiedCellAddresses;                          // Contains already occupied grid cells.
    vector<INT> _IncludedPatterns;                                  // Contains the used room patterns.
    BOOL *_UseStartCrosshair = new BOOL();                          // Do we use or not use the starting crosshair?
    INT *_NumberOfRooms = new INT();                                // Contains number of rooms.
    INT *_FieldSizeLine = new INT();                                // Contains the size of the field in height.
    INT *_FieldSizeColumn = new INT();                              // Contains the size of the field in length.
    INT *_CoordinateStartRoomLine = new INT();                      // Contains the height coordinate of the starting room.
    INT *_CoordinateStartRoomColumn = new INT();                    // Contains the length coordinate of the starting room.

    /*=====================
      Core private methods
     =====================*/
    vector <vector<DOUBLE>>
    CalculateOfRoomCellsCoordinates(INT Line,
                                    INT Column);

    BOOL
    IsOccupiedCoordinates(DOUBLE Coordinates);

    BOOL
    IsOutOfFieldCoordinates(DOUBLE Coordinates);

    DOUBLE
    TranslateCoordinates(INT ToCompressedOrToEditable,
                         INT GetColumnOrLine,
                         DOUBLE Coordinates,
                         INT Line,
                         INT Column);

    VOID
    VerifyParameter();

    VOID
    CreateStartCrosshair();

    VOID
    CreateRoom(INT RoomMode);

    VOID
    AddRoomToVector(shared_ptr<BaseRoomPattern> Room);

    VOID
    CheckRoom(INT Room);

    vector<INT>
    TestAndSortPatterns(shared_ptr<BaseRoomPattern> Room,
                        INT Direction);

    VOID
    PrintResult();

public:     
    Generator();
    ~Generator();

    /*====================
      Core public methods
     ====================*/
    STATUS
    Configure(INT FieldSizeLine,
              INT FieldSizeColumn,
              INT CoordinateStartRoomLine,
              INT CoordinateStartRoomColumn,
              INT NumberOfRoom,
              BOOL UseStartCrosshair,
              vector<INT> IncludedPatterns);

    STATUS
    Generate();
};


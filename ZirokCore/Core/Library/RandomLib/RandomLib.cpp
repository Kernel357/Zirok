/*Stub functions are stored here for now*/

#include "Core/Library/RandomLib/RandomLib.h"
#include "Core/Library/DebugLib/DebugLib.h"

INT
Get_RandomDirection(shared_ptr<BaseRoomPattern> Room)
{
    DebugPrintMessange(SERVICE_INFO, "Time: %d \n", time(0));
    srand(time(0));
    INT RandomDirection = 0;
    vector<INT> FreeDirections = Room->Get_FreeDirections();

    if(!FreeDirections.empty())
    {
        RandomDirection = FreeDirections.at(rand() % FreeDirections.size());
    }

    return RandomDirection;
}

INT
Get_RandomPattern(vector<INT> SortedPatterns)
{
    DebugPrintMessange(SERVICE_INFO, "Time: %d \n", time(0));
    srand(time(0));
    return SortedPatterns.at(rand() % SortedPatterns.size());
}

INT
Get_RandomRoom(vector<shared_ptr<BaseRoomPattern>> SortedParentRooms)
{
    DebugPrintMessange(SERVICE_INFO, "Time: %d \n", time(0));
    srand(time(0));
    return rand() % SortedParentRooms.size() + 1;
}


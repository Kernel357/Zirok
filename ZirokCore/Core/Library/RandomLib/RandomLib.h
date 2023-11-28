#include <memory>
#include <vector>
#include "Core/BaseDef/BaseDef.h"
#include "Core/RoomPatterns/RoomPatterns.h"

using namespace std;

INT
Get_RandomDirection(shared_ptr<BaseRoomPattern> Room);

INT
Get_RandomPattern(vector<INT> IncludedPatterns);

INT
Get_RandomRoom(vector<shared_ptr<BaseRoomPattern>> SortedParentRooms);

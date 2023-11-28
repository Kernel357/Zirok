#include "zirokcore.h"
#include "Core/Generator/Generator.h"
#include "Core/Library/DebugLib/DebugLib.h"

ZirokCore::ZirokCore()
{

}

ZirokCore::~ZirokCore(){

}

std::string ZirokCore::Main(int FieldSizeLine,
                            int FieldSizeColumn,
                            int CoordinateStartRoomLine,
                            int CoordinateStartRoomColumn,
                            int NumberOfRooms,
                            bool UseStartCrosshair,
                            vector<int> IncludedPatterns)
{
    Generator *generator = new Generator();

    STATUS Status = generator->Configure(FieldSizeLine,
                                         FieldSizeColumn,
                                         CoordinateStartRoomLine,
                                         CoordinateStartRoomColumn,
                                         NumberOfRooms,
                                         UseStartCrosshair,
                                         IncludedPatterns);

    if(Status == SUCCESS)
    {
        Status = generator->Generate();
    }

    DebugPrintMessange(INFO, "Status: %s\n", Status);

    delete generator;

    IteratorStatusMap = StatusMap.find(Status);
    return IteratorStatusMap->second;
}

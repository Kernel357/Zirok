#ifndef ZIROKCORE_H
#define ZIROKCORE_H

#include "ZirokCore_global.h"
#include <string>
#include <vector>

using namespace std;

class ZIROKCORE_EXPORT ZirokCore
{
public:
    ZirokCore();
    ~ZirokCore();
    string Main(int FieldSizeLine,
                int FieldSizeColumn,
                int CoordinateStartRoomLine,
                int CoordinateStartRoomColumn,
                int NumberOfRoom,
                bool UseStartCrosshair,
                vector<int> IncludedPatterns);
};

#endif // ZIROKCORE_H

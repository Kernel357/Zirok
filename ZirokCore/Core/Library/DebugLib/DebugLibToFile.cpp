#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <stdarg.h>
#include "Core/Library/DebugLib/DebugLib.h"

std::ofstream LogOutToFile;

VOID
DebugPrintMessange(DEBUG_MESSANGE_TYPES Type,
                   STRING_VIEW String, ...)
{
    std::vector<DEBUG_MESSANGE_TYPES>::iterator IteratorEnabledMessangeTypes = find(EnabledDebugMessangeTypes.begin(), EnabledDebugMessangeTypes.end(), Type);
    if(IteratorEnabledMessangeTypes == EnabledDebugMessangeTypes.end())
    {
        return;
    }

    va_list ArgList;
    va_start(ArgList, String);

    for(INT i = 0; i < String.size(); i++)
    {
        if(String[i] == '%')
        {
            switch (String[++i])
            {
                case 'd':
                {
                    INT IntValue = va_arg(ArgList, INT);
                    LogOutToFile << IntValue;
                    break;
                }

                case 'f':
                {
                    DOUBLE DoubleValue = va_arg(ArgList, DOUBLE);
                    LogOutToFile << DoubleValue;
                    break;
                }

                case 'c':
                {
                    CHAR CharValue = va_arg(ArgList, INT);
                    LogOutToFile << CharValue;
                    break;
                }

                case 'b':
                {
                    BOOL BoolValue = va_arg(ArgList, INT);

                    if(BoolValue == 1)
                    {
                        LogOutToFile << "true";
                    }

                    else
                    {
                        LogOutToFile << "false";
                    }

                    break;
                }

                case 's':
                {
                    IteratorStatusMap = StatusMap.find(va_arg(ArgList, INT));

                    if(IteratorStatusMap != StatusMap.end())
                    {
                        LogOutToFile<<IteratorStatusMap->second;
                        break;
                    }

                    LogOutToFile<<"UNKNOWN";
                    break;
                }
            }
        }

        else if(String[i] == '\\')
        {
            switch (String[++i])
            {
                case 'n':
                {
                    LogOutToFile<<std::endl;
                    break;
                }
            }
        }

        else
        {
            LogOutToFile<<String[i];
        }
    }

    va_end(ArgList);

    return;
}

VOID
DeadLoop()
{
    while(true);
}

VOID
InitLog()
{
    LogOutToFile.open("../log.txt");
}

VOID
DeInitLog()
{
    LogOutToFile.close();
}

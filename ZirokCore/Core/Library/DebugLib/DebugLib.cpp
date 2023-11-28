#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <stdarg.h>
#include "Core/Library/DebugLib/DebugLib.h"

using namespace std;

VOID DebugPrintMessange(DEBUG_MESSANGE_TYPES Type,
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
                    cout << IntValue;
                    break;
                }

                case 'f':
                {
                    DOUBLE DoubleValue = va_arg(ArgList, DOUBLE);
                    cout << DoubleValue;
                    break;
                }

                case 'c':
                {
                    CHAR CharValue = va_arg(ArgList, INT);
                    cout << CharValue;
                    break;
                }

                case 's':
                {
                    IteratorStatusMap = StatusMap.find(va_arg(ArgList, INT));

                    if(IteratorStatusMap != StatusMap.end())
                    {
                        cout<<IteratorStatusMap->second;
                        break;
                    }

                    cout<<"UNKNOWN";
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
                    cout<<endl;
                    break;
                }
            }
        }

        else
        {
            cout<<String[i];
        }
    }

    va_end(ArgList);

    return;
}

VOID DeadLoop()
{
    while(true);
}

VOID InitLog()
{
    return;
}

VOID DeInitLog()
{
    return;
}

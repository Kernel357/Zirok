#include <math.h>
#include "Generator.h"

/*
 * DOUBLE
 * Generator::TranslateCoordinates()
 *
 * This method will allow you to convert coordinates from a compressed system to an editable system.
 * We use it to make it easier to work with coordinates in editable mode, as well as compactly store coordinates in a compressed system.
 * The compressed system is a DOUBLE number, and the edited system is two int numbers - line and column coordinates.
 *
 * @params:
 *      INT ToCompressedOrToEditable,
 *      INT GetLineOrColumn,
 *      DOUBLE Coordinates,
 *      INT Line,
 *      INT Column
 *
 * @return:
 *      DOUBLE Coordinate OR DOUBLE Coordinates
*/

DOUBLE
Generator::TranslateCoordinates(INT ToCompressedOrToEditable,
                                INT GetLineOrColumn,
                                DOUBLE Coordinates,
                                INT Line,
                                INT Column)
{
    if(ToCompressedOrToEditable == 0)
    {
        return static_cast<DOUBLE>(Line + Column * 0.01);
    }

    else if(ToCompressedOrToEditable == 1)
    {
        if(GetLineOrColumn == 0)
        {
            return trunc(Coordinates);
        }

        else if(GetLineOrColumn == 1)
        {
            return round((Coordinates - trunc(Coordinates)) * 100);
        }
    }

    return 0;
}


/*
 * DOUBLE
 * Generator::IsOccupiedCoordinates()
 *
 * This method allows you to check that the coordinates are not already occupied by another room.
 *
 * @params:
 *      DOUBLE Coordinates
 *
 * @return:
 *      true OR false
*/

BOOL
Generator::IsOccupiedCoordinates(DOUBLE Coordinates)
{
    for(INT i = 0; i < _OccupiedCellAddresses.size(); i++)
    {
        if(_OccupiedCellAddresses.at(i) == Coordinates)
        {
            DebugPrintMessange(SERVICE_INFO, "Coordinates: %f is occupied! \n", Coordinates);
            return true;
        }
    }

    return false;
}


/*
 * DOUBLE
 * Generator::IsOutOfFieldCoordinates()
 *
 * This method allows you to check that the coordinates are not outside the field.
 *
 * @params:
 *      DOUBLE Coordinates
 *
 * @return:
 *      true OR false
*/

BOOL
Generator::IsOutOfFieldCoordinates(DOUBLE Coordinates)
{
    INT Line = TranslateCoordinates(EDITABLE, LINE, Coordinates, NULL, NULL);
    INT Column = TranslateCoordinates(EDITABLE, COLUMN, Coordinates, NULL, NULL);

    if(Line > *_FieldSizeLine || Line <= 0 || Column > *_FieldSizeColumn || Column <= 0)
    {
        DebugPrintMessange(SERVICE_INFO, "Coordinates: Line: %d Column: %d is out of field! \n", Line, Column);
        return true;
    }

    return false;
}


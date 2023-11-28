#include "Generator.h"


/*
 * vector<INT>
 * Generator::TestingAndSortingPatterns()
 *
 * We can use this method to fill a vector with patterns that can become patterns
 *      for the next child room based on free space in the chosen direction.
 *
 * @params:
 *      shared_ptr<BaseRoomPattern> Room        Parent room.
 *      INT Direction                           Direction of generation.
 *
 * @return:
 *      vector<INT> SortedPatterns              Patterns that can be used in the current generate iteration.
*/

vector<INT>
Generator::TestingAndSortingPatterns(shared_ptr<BaseRoomPattern> Room,
                                     INT Direction)
{
    vector<INT> SortedPatterns;
    INT Pattern = 0;

    DOUBLE Coordinates = 0;

    INT Line = 0;
    INT Column = 0;

    for(INT i = 0; i < _IncludedPatterns.size(); i++)
    {
        DebugPrintMessange(SERVICE_INFO, "Check pattern: %d: \n", _IncludedPatterns.at(i));
        Coordinates = Room->SetOrGet_RoomCellCoordinates(GET, Direction, NULL);

        Line = TranslateCoordinates(EDITABLE, LINE, Coordinates, NULL, NULL);
        Column = TranslateCoordinates(EDITABLE, COLUMN, Coordinates, NULL, NULL);

        *_Status = SUCCESS;

        Pattern = _IncludedPatterns.at(i);

        if(Pattern == 1)
        {
            SortedPatterns.push_back(Pattern);
            DebugPrintMessange(SERVICE_INFO, "Pattern: %d added to SortedPatterns\n", Pattern);
        }

        else if(Pattern == 2)
        {
            if(*_CellIterator - 2 < 0)
            {
                continue;
            }

            for(INT f = 0; f < 2; f++)
            {
                if(*_Direction == 1)
                {
                    if(f == 0)
                    {
                        //First room cell
                        Line--;
                    }

                    else if(f == 1)
                    {
                        //Second room cell
                        Line--;
                    }
                }

                else if(*_Direction == 2)
                {
                    if(f == 0)
                    {
                        //First room cell
                        Column++;
                    }

                    else if(f == 1)
                    {
                        //Second room cell
                        Line--;
                    }
                }

                else if(*_Direction == 3)
                {
                    if(f == 0)
                    {
                        //First room cell
                        Line++;
                    }

                    else if(f == 1)
                    {
                        //Second room cell
                        Line++;
                    }
                }

                else if(*_Direction == 4)
                {
                    if(f == 0)
                    {
                        //First room cell
                        Column--;
                    }

                    else if(f == 1)
                    {
                        //Second room cell
                        Line++;
                    }
                }

                Coordinates = TranslateCoordinates(COMPRESSED, NULL, NULL, Line, Column);

                if(IsOutOfFieldCoordinates(Coordinates) || IsOccupiedCoordinates(Coordinates))
                {
                    *_Status = PATTERN_DOES_NOT_FIT;
                    f = 2;
                }
            }

            if(*_Status != SUCCESS)
            {
                continue;
            }

            SortedPatterns.push_back(Pattern);
            DebugPrintMessange(SERVICE_INFO, "Pattern: %d added to SortedPatterns\n", Pattern);
        }

        else if(Pattern == 3)
        {
            if(*_CellIterator - 2 < 0)
            {
                continue;
            }

            for(INT f = 0; f < 2; f++)
            {
                if(*_Direction == 1)
                {
                    if(f == 0)
                    {
                        //First room cell
                        Line--;
                    }

                    else if(f == 1)
                    {
                        //Second room cell
                        Column--;
                    }
                }

                else if(*_Direction == 2)
                {
                    if(f == 0)
                    {
                        //First room cell
                        Column++;
                    }

                    else if(f == 1)
                    {
                        //Second room cell
                        Column++;
                    }
                }

                else if(*_Direction == 3)
                {
                    if(f == 0)
                    {
                        //First room cell
                        Line++;
                    }

                    else if(f == 1)
                    {
                        //Second room cell
                        Column++;
                    }
                }

                else if(*_Direction == 4)
                {
                    if(f == 0)
                    {
                        //First room cell
                        Column--;
                    }

                    else if(f == 1)
                    {
                        //Second room cell
                        Column--;
                    }
                }

                Coordinates = TranslateCoordinates(COMPRESSED, NULL, NULL, Line, Column);

                if(IsOutOfFieldCoordinates(Coordinates) || IsOccupiedCoordinates(Coordinates))
                {
                    *_Status = PATTERN_DOES_NOT_FIT;
                    f = 2;
                }
            }

            if(*_Status != SUCCESS)
            {
                continue;
            }

            SortedPatterns.push_back(Pattern);
            DebugPrintMessange(SERVICE_INFO, "Pattern: %d added to SortedPatterns\n", Pattern);
        }

        else if(Pattern == 4)
        {
            if(*_CellIterator - 3 < 0)
            {
                continue;
            }

            for(INT f = 0; f < 3; f++)
            {
                if(*_Direction == 1)
                {
                    if(f == 0)
                    {
                        //First room cell
                        Line--;
                    }

                    else if(f == 1)
                    {
                        //Second room cell
                        Line--;
                    }

                    else if(f == 2)
                    {
                        //Third room cell
                        Column++;
                    }
                }

                else if(*_Direction == 2)
                {
                    if(f == 0)
                    {
                        //First room cell
                        Column++;
                    }

                    else if(f == 1)
                    {
                        //Second room cell
                        Line--;
                    }

                    else if(f == 2)
                    {
                        //Third room cell
                        Column++;
                    }
                }

                else if(*_Direction == 3)
                {
                    if(f == 0)
                    {
                        //First room cell
                        Line++;
                    }

                    else if(f == 1)
                    {
                        //Second room cell
                        Column--;
                    }

                    else if(f == 2)
                    {
                        //Third room cell
                        Line++;
                    }
                }

                else if(*_Direction == 4)
                {
                    if(f == 0)
                    {
                        //First room cell
                        Column--;
                    }

                    else if(f == 1)
                    {
                        //Second room cell
                        Column--;
                    }

                    else if(f == 2)
                    {
                        //Third room cell
                        Line++;
                    }
                }

                Coordinates = TranslateCoordinates(COMPRESSED, NULL, NULL, Line, Column);

                if(IsOutOfFieldCoordinates(Coordinates) || IsOccupiedCoordinates(Coordinates))
                {
                    *_Status = PATTERN_DOES_NOT_FIT;
                    f = 3;
                }
            }

            if(*_Status != SUCCESS)
            {
                continue;
            }

            SortedPatterns.push_back(Pattern);
            DebugPrintMessange(SERVICE_INFO, "Pattern: %d added to SortedPatterns\n", Pattern);
        }

        else if(Pattern == 5)
        {
            if(*_CellIterator - 3 < 0)
            {
                continue;
            }

            for(INT f = 0; f < 3; f++)
            {
                if(*_Direction == 1)
                {
                    if(f == 0)
                    {
                        //First room cell
                        Line--;
                    }

                    else if(f == 1)
                    {
                        //Second room cell
                        Column--;
                    }

                    else if(f == 2)
                    {
                        //Third room cell
                        Line--;
                    }
                }

                else if(*_Direction == 2)
                {
                    if(f == 0)
                    {
                        //First room cell
                        Column++;
                    }

                    else if(f == 1)
                    {
                        //Second room cell
                        Line++;
                    }

                    else if(f == 2)
                    {
                        //Third room cell
                        Column++;
                    }
                }

                else if(*_Direction == 3)
                {
                    if(f == 0)
                    {
                        //First room cell
                        Line++;
                    }

                    else if(f == 1)
                    {
                        //Second room cell
                        Line++;
                    }

                    else if(f == 2)
                    {
                        //Third room cell
                        Column++;
                    }
                }

                else if(*_Direction == 4)
                {
                    if(f == 0)
                    {
                        //First room cell
                        Column--;
                    }

                    else if(f == 1)
                    {
                        //Second room cell
                        Column--;
                    }

                    else if(f == 2)
                    {
                        //Third room cell
                        Line--;
                    }
                }

                Coordinates = TranslateCoordinates(COMPRESSED, NULL, NULL, Line, Column);

                if(IsOutOfFieldCoordinates(Coordinates) || IsOccupiedCoordinates(Coordinates))
                {
                    *_Status = PATTERN_DOES_NOT_FIT;
                    f = 3;
                }
            }

            if(*_Status != SUCCESS)
            {
                continue;
            }

            SortedPatterns.push_back(Pattern);
            DebugPrintMessange(SERVICE_INFO, "Pattern: %d added to SortedPatterns\n", Pattern);
        }

        else if(Pattern == 6)
        {
            if(*_CellIterator - 3 < 0)
            {
                continue;
            }

            for(INT f = 0; f < 3; f++)
            {
                if(*_Direction == 1)
                {
                    if(f == 0)
                    {
                        //First room cell
                        Line--;
                    }

                    else if(f == 1)
                    {
                        //Second room cell
                        Line--;
                    }

                    else if(f == 2)
                    {
                        //Third room cell
                        Column--;
                    }
                }

                else if(*_Direction == 2)
                {
                    if(f == 0)
                    {
                        //First room cell
                        Column++;
                    }

                    else if(f == 1)
                    {
                        //Second room cell
                        Column++;
                    }

                    else if(f == 2)
                    {
                        //Third room cell
                        Line++;
                    }
                }

                else if(*_Direction == 3)
                {
                    if(f == 0)
                    {
                        //First room cell
                        Line++;
                    }

                    else if(f == 1)
                    {
                        //Second room cell
                        Column++;
                    }

                    else if(f == 2)
                    {
                        //Third room cell
                        Line++;
                    }
                }

                else if(*_Direction == 4)
                {
                    if(f == 0)
                    {
                        //First room cell
                        Column--;
                    }

                    else if(f == 1)
                    {
                        //Second room cell
                        Line--;
                    }

                    else if(f == 2)
                    {
                        //Third room cell
                        Column--;
                    }
                }

                Coordinates = TranslateCoordinates(COMPRESSED, NULL, NULL, Line, Column);

                if(IsOutOfFieldCoordinates(Coordinates) || IsOccupiedCoordinates(Coordinates))
                {
                    *_Status = PATTERN_DOES_NOT_FIT;
                    f = 3;
                }
            }

            if(*_Status != SUCCESS)
            {
                continue;
            }

            SortedPatterns.push_back(Pattern);
            DebugPrintMessange(SERVICE_INFO, "Pattern: %d added to SortedPatterns\n", Pattern);
        }

        else if(Pattern == 7)
        {
            if(*_CellIterator - 3 < 0)
            {
                continue;
            }

            for(INT f = 0; f < 3; f++)
            {
                if(*_Direction == 1)
                {
                    if(f == 0)
                    {
                        //First room cell
                        Line--;
                    }

                    else if(f == 1)
                    {
                        //Second room cell
                        Column++;
                    }

                    else if(f == 2)
                    {
                        //Third room cell
                        Line--;
                    }
                }

                else if(*_Direction == 2)
                {
                    if(f == 0)
                    {
                        //First room cell
                        Column++;
                    }

                    else if(f == 1)
                    {
                        //Second room cell
                        Column++;
                    }

                    else if(f == 2)
                    {
                        //Third room cell
                        Line--;
                    }
                }

                else if(*_Direction == 3)
                {
                    if(f == 0)
                    {
                        //First room cell
                        Line++;
                    }

                    else if(f == 1)
                    {
                        //Second room cell
                        Line++;
                    }

                    else if(f == 2)
                    {
                        //Third room cell
                        Column--;
                    }
                }

                else if(*_Direction == 4)
                {
                    if(f == 0)
                    {
                        //First room cell
                        Column--;
                    }

                    else if(f == 1)
                    {
                        //Second room cell
                        Line++;
                    }

                    else if(f == 2)
                    {
                        //Third room cell
                        Column--;
                    }
                }

                Coordinates = TranslateCoordinates(COMPRESSED, NULL, NULL, Line, Column);

                if(IsOutOfFieldCoordinates(Coordinates) || IsOccupiedCoordinates(Coordinates))
                {
                    *_Status = PATTERN_DOES_NOT_FIT;
                    f = 3;
                }
            }

            if(*_Status != SUCCESS)
            {
                continue;
            }

            SortedPatterns.push_back(Pattern);
            DebugPrintMessange(SERVICE_INFO, "Pattern: %d added to SortedPatterns\n", Pattern);
        }

        else if(Pattern == 8)
        {
            if(*_CellIterator - 4 < 0)
            {
                continue;
            }

            for(INT f = 0; f < 4; f++)
            {
                if(*_Direction == 1)
                {
                    if(f == 0)
                    {
                        //First room cell
                        Line--;
                    }

                    else if(f == 1)
                    {
                        //Second room cell
                        Line--;
                    }

                    else if(f == 2)
                    {
                        //Third room cell
                        Column++;
                    }

                    else if(f == 3)
                    {
                        //Fourth room cell
                        Line++;
                    }
                }

                else if(*_Direction == 2)
                {
                    if(f == 0)
                    {
                        //First room cell
                        Column++;
                    }

                    else if(f == 1)
                    {
                        //Second room cell
                        Column++;
                    }

                    else if(f == 2)
                    {
                        //Third room cell
                        Line++;
                    }

                    else if(f == 3)
                    {
                        //Fourth room cell
                        Column--;
                    }
                }

                else if(*_Direction == 3)
                {
                    if(f == 0)
                    {
                        //First room cell
                        Line++;
                    }

                    else if(f == 1)
                    {
                        //Second room cell
                        Line++;
                    }

                    else if(f == 2)
                    {
                        //Third room cell
                        Column--;
                    }

                    else if(f == 3)
                    {
                        //Fourth room cell
                        Line--;
                    }
                }

                else if(*_Direction == 4)
                {
                    if(f == 0)
                    {
                        //First room cell
                        Column--;
                    }

                    else if(f == 1)
                    {
                        //Second room cell
                        Column--;
                    }

                    else if(f == 2)
                    {
                        //Third room cell
                        Line--;
                    }

                    else if(f == 3)
                    {
                        //Fourth room cell
                        Column++;
                    }
                }

                Coordinates = TranslateCoordinates(COMPRESSED, NULL, NULL, Line, Column);

                if(IsOutOfFieldCoordinates(Coordinates) || IsOccupiedCoordinates(Coordinates))
                {
                    *_Status = PATTERN_DOES_NOT_FIT;
                    f = 4;
                }
            }

            if(*_Status != SUCCESS)
            {
                continue;
            }

            SortedPatterns.push_back(Pattern);
            DebugPrintMessange(SERVICE_INFO, "Pattern: %d added to SortedPatterns\n", Pattern);
        }
    }

    return SortedPatterns;
}

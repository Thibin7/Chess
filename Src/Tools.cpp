#include "../Include/Tools.h"

#include <iostream>

bool operator==(const ts_position& ai_position1, const ts_position& ai_position2)
{
  if ( (ai_position1.posX == ai_position2.posX)
    && (ai_position1.posY == ai_position2.posY) )
  {
    return true;
  }
  else
  {
    return false;
  }
}

bool operator!=(const ts_position& ai_position1, const ts_position& ai_position2)
{
  if ( (ai_position1.posX != ai_position2.posX)
    || (ai_position1.posY != ai_position2.posY) )
  {
    return true;
  }
  else
  {
    return false;
  }
}

bool operator!=(const ts_move& ai_move1, const ts_move& ai_move2)
{
  if ( (ai_move1.startPos != ai_move2.startPos)
  || (ai_move1.endPos != ai_move2.endPos) )
  {
    return true;
  }
  else
  {
    return false;
  }
}

#ifndef TOOLS_H
#define TOOLS_H

#include <string>

typedef struct
{
    int posX;
    int posY;
}ts_position;

typedef struct
{
    ts_position startPos;
    ts_position endPos;
} ts_move;

enum PieceEnum
{
  E_PAWN,
  E_ROOK,
  E_KNIGHT,
  E_BISHOP,
  E_KING,
  E_QUEEN,
  E_UNKNOWN
};

enum ColorEnum
{
  E_WHITE,
  E_BLACK,
  E_UNKNOWN_COLOR
};

bool operator==(const ts_position&, const ts_position&);
bool operator!=(const ts_position&, const ts_position&);
bool operator!=(const ts_move&, const ts_move&);

#endif

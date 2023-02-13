#ifndef PIECE_H
#define PIECE_H

#include <iostream>
#include <string>
#include "Tools.h"

class Board;

// Main piece class
class Piece
{
  public:
    Piece(PieceEnum ai_name, ColorEnum ai_color, Board * ao_board, ts_position ai_position = {0,0});
    virtual ~Piece();

    ts_position getPosition();
    void setPosition(ts_position ai_position);

    PieceEnum getName();
    ColorEnum getColor();

    virtual void displaySprite() = 0;

    virtual bool isMovementValid(ts_position ai_askedPosition) = 0;

  protected:
    PieceEnum m_name {E_UNKNOWN};
    ColorEnum m_color {E_WHITE};
    ts_position m_position {0,0};

    Board * mp_mainBoard = nullptr;

    bool _isInBoard(ts_position ai_position);

};

#endif

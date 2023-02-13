#ifndef QUEEN_H
#define QUEEN_H

#include <Piece.h>

// Queen Piece Class
class Queen : public Piece
{
  public:
    Queen(ColorEnum ai_color, Board * ao_board);
    Queen(ColorEnum ai_color, Board * ao_board, ts_position ai_position);

    ~Queen();

    void displaySprite();
    bool isMovementValid(ts_position ai_askedPosition);
};

#endif

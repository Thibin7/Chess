#ifndef KNIGHT_H
#define KNIGHT_H

#include <Piece.h>

// Knight Piece Class
class Knight : public Piece
{
  public:
    Knight(ColorEnum ai_color, Board * ao_board);
    Knight(ColorEnum ai_color, Board * ao_board, ts_position ai_position);

    ~Knight();

    void displaySprite();
    bool isMovementValid(ts_position ai_askedPosition);
};

#endif

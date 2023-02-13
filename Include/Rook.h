#ifndef ROOK_H
#define ROOK_H

#include <Piece.h>

// Rook Piece Class
class Rook : public Piece
{
  public:
    Rook(ColorEnum ai_color, Board * ao_board);
    Rook(ColorEnum ai_color, Board * ao_board, ts_position ai_position);

    ~Rook();

    void displaySprite();
    bool isMovementValid(ts_position ai_askedPosition);
};

#endif

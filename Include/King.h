#ifndef KING_H
#define KING_H

#include <Piece.h>

// King Piece Class
class King : public Piece
{
  public:
    King(ColorEnum ai_color, Board * ao_board);
    King(ColorEnum ai_color, Board * ao_board, ts_position ai_position);

    ~King();

    void displaySprite();
    bool isMovementValid(ts_position ai_askedPosition);
};

#endif

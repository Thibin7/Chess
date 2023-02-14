#ifndef BISHOP_H
#define BISHOP_H

#include <Piece.h>

// Bishop Piece Class
class Bishop : public Piece
{
  public:
    Bishop(ColorEnum ai_color, Board * ao_board);
    Bishop(ColorEnum ai_color, Board * ao_board, ts_position ai_position);

    ~Bishop();

    void displaySprite();
    bool isMovementValid(ts_position ai_askedPosition);
};

#endif

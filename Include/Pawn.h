#ifndef PAWN_H
#define PAWN_H

#include <Piece.h>

// Pawn Piece Class
class Pawn : public Piece
{
  public:
    Pawn(ColorEnum ai_color, Board * ao_board);
    Pawn(ColorEnum ai_color, Board * ao_board, ts_position ai_position);

    ~Pawn();

    void displaySprite();
    bool isMovementValid(ts_position ai_askedPosition);

  private:
    bool m_hasMoved {false};

    bool _moveOneSquare(ts_position ai_askedPosition);
    bool _moveTwoSquare(ts_position ai_askedPosition);
    bool _moveDiagonally(ts_position ai_askedPosition);
};

#endif

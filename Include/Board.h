#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include "Tools.h"


class Piece;

// Board class
class Board
{
  public:
    Board();
    ~Board();

    void displayCurrentState();
    void processMove(ts_position ai_startPosition, ts_position ai_endPosition);

    bool isPieceOnThePath(ts_position ai_startPosition, ts_position ai_endPosition);

    Piece * isPieceOnSquare(ts_position ai_position);


  private:
    std::vector<Piece *> m_currentState;
    ColorEnum m_playerColor {E_WHITE};


    void _swapPlayerColor();
    void _deletePiece(Piece * ai_deletedPiece);

    int _isDiffNeg(int w_endPos, int w_startPos);
    int _numberOfSquareBetween(ts_position ai_startPosition, ts_position ai_endPosition);
};

#endif

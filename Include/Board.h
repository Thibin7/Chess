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
    Board(std::string & ai_filePath);
    ~Board();

    void displayCurrentState();
    void processMove(ts_position ai_startPosition, ts_position ai_endPosition);

    bool isPieceOnThePath(ts_position ai_startPosition, ts_position ai_endPosition);

    Piece * isPieceOnSquare(ts_position ai_position);

    bool loadGameFile(std::string ai_filePath);


  private:
    std::vector<Piece *> m_currentState;
    ColorEnum m_playerColor {E_WHITE};

    void _createDefaultBoard();

    bool _parseFileSave(std::string & ai_readSave);
    bool _setPlayerColorFromFile(std::string & ai_playerColor);
    bool _setPieceFromFile(std::string & ai_pieceType, std::string & ai_pieceColor, std::string & ai_piecePosition);
    PieceEnum _intepretePieceType(std::string & ai_pieceType);
    ColorEnum _intepretePieceColor(std::string & ai_pieceColor);
    ts_position _intepretePiecePosition(std::string & ai_piecePosition);


    void _swapPlayerColor();

    void _deletePiece(Piece * ai_deletedPiece);
    void _clearCurrentState();

    int _isDiffNeg(int w_endPos, int w_startPos);
    int _numberOfSquareBetween(ts_position ai_startPosition, ts_position ai_endPosition);
};

#endif

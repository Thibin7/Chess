#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include "Tools.h"
#include "FileLoader.h"


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

    bool loadGameFile(std::string ai_path);

    void addPiece(PieceEnum& ai_pieceType, ColorEnum& ai_pieceColor, ts_position& ai_piecePosition);
    void setPlayerColor(ColorEnum ai_color);


  private:
    std::vector<Piece *> m_currentState;
    ColorEnum m_playerColor {E_WHITE};

    void _createDefaultBoard();

    bool _isSameColorKingCheck(Piece * ai_startPiece, ts_position & ai_endPosition);
    ts_position _getKingPosition(ColorEnum ai_kingColor);

    void _swapPlayerColor();
    std::string _getColorStr(ColorEnum ai_color);

    void _deletePiece(Piece * ai_deletedPiece);
    void _clearCurrentState();

    int _isDiffNeg(int w_endPos, int w_startPos);
    int _numberOfSquareBetween(ts_position ai_startPosition, ts_position ai_endPosition);
};

#endif

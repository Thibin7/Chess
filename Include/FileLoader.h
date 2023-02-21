#ifndef FILELOADER_H
#define FILELOADER_H

#include <string>
#include <vector>

#include "Piece.h"

class Board;

// FileLoader class
class FileLoader
{
  public:
    FileLoader(Board * ai_board);
    ~FileLoader();

    bool loadGameFile(std::string ai_filePath );

  private:

    Board * mp_currentBoard;

    bool _parseFileSave(std::string & ai_readSave);
    bool _setPlayerColorFromFile(std::string & ai_playerColor);
    bool _setPieceFromFile(std::string & ai_pieceType, std::string & ai_pieceColor, std::string & ai_piecePosition);
    PieceEnum _intepretePieceType(std::string & ai_pieceType);
    ColorEnum _intepretePieceColor(std::string & ai_pieceColor);
    ts_position _intepretePiecePosition(std::string & ai_piecePosition);

};

#endif

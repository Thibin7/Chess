#include "../Include/FileLoader.h"
#include "../Include/Logger.h"
#include "../Include/Constants.h"
#include "../Include/Board.h"

#include "../Include/Rook.h"
#include "../Include/Knight.h"
#include "../Include/Bishop.h"
#include "../Include/Queen.h"
#include "../Include/King.h"
#include "../Include/Pawn.h"


#include <fstream>

// Default constructor
FileLoader::FileLoader(Board * ai_board) : mp_currentBoard(ai_board)
{}

// Destructor
FileLoader::~FileLoader()
{}

// Load a file game save
// Return true if the file has been correctly loaded
bool FileLoader::loadGameFile(std::string ai_filePath)
{
  // If no file is given
  if (ai_filePath.empty())
  {
    TraceLog::logger.warning(LOG_SOFT, "File path is empty : file not loaded !");
    return false;
  }

  // Create file stream
  std::ifstream w_loadedFile;
  w_loadedFile.open(ai_filePath);

  // If an error occured while opening file
  if ( !w_loadedFile.is_open() )
  {
    TraceLog::logger.warning(LOG_SOFT, "Cannot open file : file not loaded !");
    return false;
  }
  else
  {
    // Reading first line of file
    std::string w_readSave;
    std::getline(w_loadedFile, w_readSave);

    // Parsing save file
    if ( !_parseFileSave(w_readSave) )
    {
        w_loadedFile.close();
        return false;
    }
  }

  TraceLog::logger.info(LOG_SOFT, "File successfuly loaded !");
  w_loadedFile.close();
  return true;
}


// Parse what we read from the save file
bool FileLoader::_parseFileSave(std::string & ai_readSave)
{
  // If what we read is empty
  if ( ai_readSave.empty() )
  {
    TraceLog::logger.warning(LOG_SOFT, "Nothing to read in save file : file not loaded !");
    return false;
  }
  // Getting the player color turn
  std::string w_playerTurn = ai_readSave.substr(0,1);
  if ( !_setPlayerColorFromFile(w_playerTurn) )
  {
    return false;
  }

  std::string w_pieceType;
  std::string w_pieceColor;
  std::string w_piecePosition;

  int w_readFileLen = ai_readSave.length();
  int w_count = 1; // We start at the second caractere

  // Reading information piece by piece
  while ( w_count < w_readFileLen )
  {
    try
    {
      w_pieceType = ai_readSave.substr(w_count,1);
      w_pieceColor = ai_readSave.substr(w_count + 1,1);
      w_piecePosition = ai_readSave.substr(w_count + 2,2);
    }
    catch (std::exception &e)
    {
      TraceLog::logger.error(LOG_SOFT, "Exception caught : %s", e.what());
      return false;
    }
    w_count += 4;

    // If an error occurs when piece is construct
    if ( !_setPieceFromFile(w_pieceType, w_pieceColor, w_piecePosition) )
    {
      TraceLog::logger.warning(LOG_SOFT, "Unable to load piece number %i : file not loaded !", (w_count - 1)/4);
      return false;
    }
  }

  return true;
}

// Set the player to play
bool FileLoader::_setPlayerColorFromFile(std::string & ai_playerColor)
{
  if (ai_playerColor == "b" )
  {
    mp_currentBoard->setPlayerColor(E_BLACK);
    return true;
  }
  else if ( ai_playerColor == "w" )
  {
    mp_currentBoard->setPlayerColor(E_WHITE);
    return true;
  }
  else
  {
    std::cout << "[WARNING] Unable to find player turn : file not loaded !" << std::endl;
    return false;
  }
}

// Create piece and add it to the current state
bool FileLoader::_setPieceFromFile(std::string & ai_pieceType, std::string & ai_pieceColor, std::string & ai_piecePosition)
{
  // Interpreting pieces informations
  PieceEnum w_pieceType = _intepretePieceType(ai_pieceType);
  ColorEnum w_pieceColor = _intepretePieceColor(ai_pieceColor);
  ts_position w_piecePosition = _intepretePiecePosition(ai_piecePosition);

  if ( w_pieceType == E_UNKNOWN )
  {
    TraceLog::logger.warning(LOG_SOFT, "Unable to find piece Type");
    return false;
  }

  if ( w_pieceColor == E_UNKNOWN_COLOR )
  {
    TraceLog::logger.warning(LOG_SOFT, "Unable to find piece Color");
    return false;
  }

  if ( w_piecePosition == Constants::C_EOF_POSITION )
  {
    TraceLog::logger.warning(LOG_SOFT, "Unable to find piece Position");
    return false;
  }

  mp_currentBoard->addPiece(w_pieceType, w_pieceColor, w_piecePosition);

  return true;
}

// Interprete the piece type from the string
PieceEnum FileLoader::_intepretePieceType(std::string & ai_pieceType)
{
  if (ai_pieceType == "c")
  {
    return E_KNIGHT;
  }
  else if (ai_pieceType == "r")
  {
    return E_ROOK;
  }
  else if (ai_pieceType == "b")
  {
    return E_BISHOP;
  }
  else if (ai_pieceType == "q")
  {
    return E_QUEEN;
  }
  else if (ai_pieceType == "k")
  {
    return E_KING;
  }
  else if (ai_pieceType == "p")
  {
    return E_PAWN;
  }
  else
  {
    return E_UNKNOWN;
  }
}

// Interprete the piece color form the string
ColorEnum FileLoader::_intepretePieceColor(std::string & ai_pieceColor)
{
  if (ai_pieceColor == "b")
  {
    return E_BLACK;
  }
  else if (ai_pieceColor == "w")
  {
    return E_WHITE;
  }
  else
  {
    return E_UNKNOWN_COLOR;
  }
}

// Interprete the piece position form the string
ts_position FileLoader::_intepretePiecePosition(std::string & ai_piecePosition)
{
  if (ai_piecePosition.length() < 2)
  {
    return Constants::C_EOF_POSITION;
  }

  // We convert the first input to an int using ASCII soustraction
  int w_posX  = ai_piecePosition[0] - 'a' + '1';
  int w_posY  = ai_piecePosition[1] - 'a' + '1';

  if ( (abs(w_posX) > 7)
    || (abs(w_posY) > 7) )
  {
      return Constants::C_EOF_POSITION;
  }

  return {w_posX, w_posY};
}

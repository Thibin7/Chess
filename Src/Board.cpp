#include "../Include/Board.h"
#include "../Include/Constants.h"
#include "../Include/Piece.h"
#include "../Include/Logger.h"

#include <iostream>
#include <fstream>

#include "../Include/Rook.h"
#include "../Include/Knight.h"
#include "../Include/Bishop.h"
#include "../Include/Queen.h"
#include "../Include/King.h"
#include "../Include/Pawn.h"


// Default constructor
Board::Board()
{
  _createDefaultBoard();
}

// Construtor
Board::Board(std::string & ai_filePath)
{
  if (ai_filePath.empty())
  {
    _createDefaultBoard();
  }
  else // If a file path to load is given
  {
    // If game save file is not loaded we create a game by default
    if ( !loadGameFile(ai_filePath) )
    {
      _createDefaultBoard();
    }
  }
}

// Destructor
Board::~Board()
{

  // Deletion of every Pieces left on the Board
  std::vector<Piece *>::iterator it_currentState = m_currentState.begin();

  for (; it_currentState != m_currentState.end(); it_currentState++)
  {
      delete *it_currentState;
  }
}

// Display in the standard output the current state of the board
void Board::displayCurrentState()
{
  // Display the first layer
  std::cout << std::endl << "   ---------------------------------" << std::endl;

  // We start the display of the board on the up left corner {0,7}
  // For every row
  for (int w_heightCounter = Constants::C_BOARD_HEIGTH - 1; w_heightCounter >= 0; w_heightCounter--)
  {
    // Display the number of the row
    std::cout << w_heightCounter + 1 << "  ";

    // For every column
    for (int w_widthCounter = 0; w_widthCounter < Constants::C_BOARD_WIDTH; w_widthCounter++)
    {
      // Display the first side of the square
      std::cout << "|";

      // Check if the square has a piece on it
      ts_position w_square = {w_widthCounter,w_heightCounter};
      Piece * w_piece = isPieceOnSquare(w_square);

      // If a piece is on the square display the piece
      if ( w_piece != nullptr)
      {
        w_piece->displaySprite();
      }
      else // Otherwise display blank
      {
          std::cout << "   ";
      }
    }
    // Display the second side of the last square
    std::cout << "|" << std::endl;
    // Display the down layer
    std::cout << "   ---------------------------------" << std::endl;
  }
  // Display the number of the column
  std::cout << std::endl << "     a   b   c   d   e   f   g   h" << std::endl << std::endl;
}

// Loading a file
bool Board::loadGameFile(std::string ai_path)
{
    FileLoader w_fileLoader(this);
    _clearCurrentState();

    return w_fileLoader.loadGameFile(ai_path);
}

void Board::processMove(ts_position ai_startPosition, ts_position ai_endPosition)
{
  Piece * w_startPiece = isPieceOnSquare(ai_startPosition);
  Piece * w_endPiece = isPieceOnSquare(ai_endPosition);

  // If no piece is on the square
  if ( w_startPiece == nullptr )
  {
    TraceLog::logger.info(LOG_GAME, "There is no piece on that square !");
    return ;
  }

  // If the piece is not the same color as the player to play
  if ( w_startPiece->getColor() != m_playerColor )
  {
    std::string w_playerColor = _getColorStr(m_playerColor);
    TraceLog::logger.info(LOG_GAME, "Piece is not the right color : it is %s player turn !", w_playerColor.c_str());
    return ;
  }

  // If the movement is a valid piece movement
  if ( !w_startPiece->isMovementValid(ai_endPosition) )
  {
    TraceLog::logger.info(LOG_GAME, "Movement not valid for that piece !");
    return ;
  }

  // If a piece of the same color is on the targeted Square
  if ( (w_endPiece != nullptr) && (w_startPiece->getColor() == w_endPiece->getColor()) )
  {
    std::string w_pieceColor = _getColorStr(w_startPiece->getColor());
    TraceLog::logger.info(LOG_GAME, "Movement not valid, a piece of the same color {%s} is on the square !", w_pieceColor.c_str());
    return ;
  }

  // If the same color king is check
  if ( _isSameColorKingCheck(w_startPiece, ai_endPosition) )
  {
    std::string w_pieceColor = _getColorStr(w_startPiece->getColor());
    TraceLog::logger.info(LOG_GAME, "Movement not valid, your king {%s} is check !", w_pieceColor.c_str());
    return ;
  }

  // If all is OK we delete the endPiece (if exists), we move the piece and swap the player color
  _deletePiece(w_endPiece);
  w_startPiece->setPosition(ai_endPosition);
  _swapPlayerColor();
}


// Check if a piece is on the path
bool Board::isPieceOnThePath(ts_position ai_startPosition, ts_position ai_endPosition)
{
  int w_numberOfSquare = _numberOfSquareBetween(ai_startPosition, ai_endPosition);

  for ( int w_counter = 1 ; w_counter < w_numberOfSquare; w_counter++)
  {
    int w_posX = ai_startPosition.posX + _isDiffNeg(ai_endPosition.posX, ai_startPosition.posX) * w_counter;
    int w_posY = ai_startPosition.posY + _isDiffNeg(ai_endPosition.posY, ai_startPosition.posY) * w_counter;

    if (isPieceOnSquare({w_posX, w_posY}) != nullptr)
    {
      return true;
    }
  }

  return false;
}

// Check if a piece is on the given positions
// If a piece is found it's returned
Piece * Board::isPieceOnSquare(ts_position ai_position)
{
  std::vector<Piece *>::iterator it_currentState = m_currentState.begin();

  for (; it_currentState != m_currentState.end(); it_currentState++)
  {
      if ( (*it_currentState)->getPosition() == ai_position)
      {
        return *it_currentState;
      }
  }

  return nullptr;
}

// Add a piece into the current state
void Board::addPiece(PieceEnum& ai_pieceType, ColorEnum& ai_pieceColor, ts_position& ai_piecePosition)
{
  // Create piece and adding it into the piece vector
  switch (ai_pieceType)
  {
    case E_PAWN:
    {
      m_currentState.push_back(new Pawn(ai_pieceColor, this, ai_piecePosition));
      break;
    }
    case E_KNIGHT:
    {
      m_currentState.push_back(new Knight(ai_pieceColor, this,  ai_piecePosition));
      break;
    }
    case E_BISHOP:
    {
      m_currentState.push_back(new Bishop(ai_pieceColor, this, ai_piecePosition));
      break;
    }
    case E_ROOK:
    {
      m_currentState.push_back(new Rook(ai_pieceColor, this, ai_piecePosition));
      break;
    }
    case E_QUEEN:
    {
      m_currentState.push_back(new Queen(ai_pieceColor, this, ai_piecePosition));
      break;
    }
    case E_KING:
    {
      m_currentState.push_back(new King(ai_pieceColor, this, ai_piecePosition));
      break;
    }
    default:
    {}
  }
}

// Setter of playerColor
void Board::setPlayerColor(ColorEnum ai_color)
{
  m_playerColor = ai_color;
}

bool Board::_isSameColorKingCheck(Piece * ai_startPiece, ts_position & ai_endPosition)
{
  // Saving actual piece position
  ts_position w_startPiecePosition = ai_startPiece->getPosition();

  // Getting same color king position
  ts_position w_sameColorKingPos = _getKingPosition(ai_startPiece->getColor());

  // Simulate piece movement
  ai_startPiece->setPosition(ai_endPosition);

  // For every piece of the opposite color we check if he can take the king
  std::vector<Piece *>::iterator w_pieceIt = m_currentState.begin();
  for (; w_pieceIt != m_currentState.end(); w_pieceIt++)
  {
    // If the piece is of the other Color
    // If the piece is not at the moved position
    // If the movement of that piece on the king is valid
    if ( ((*w_pieceIt)->getColor() != ai_startPiece->getColor())
      && ((*w_pieceIt)->getPosition() != ai_endPosition )
      && (*w_pieceIt)->isMovementValid(w_sameColorKingPos) )
    {
      // Repositionning piece on old square
      ai_startPiece->setPosition(w_startPiecePosition);
      return true;
    }
  }

  ai_startPiece->setPosition(w_startPiecePosition);
  return false;
}

// Getting the king position of the given color
ts_position Board::_getKingPosition(ColorEnum ai_kingColor)
{
  std::vector<Piece *>::iterator w_pieceIt = m_currentState.begin();

  for (; w_pieceIt != m_currentState.end(); w_pieceIt++)
  {
    if ( ((*w_pieceIt)->getColor() == ai_kingColor) && (*w_pieceIt)->getName() == E_KING )
    {
      return (*w_pieceIt)->getPosition();
    }
  }

  // Shouldn't append !
  return Constants::C_EOF_POSITION;
}

// Create default board
void Board::_createDefaultBoard()
{
  _clearCurrentState();

  // Creation of white Rooks
  m_currentState.push_back(new Rook(E_WHITE, this, {0,0}));
  m_currentState.push_back(new Rook(E_WHITE, this, {7,0}));
  // Creation of white Knights
  m_currentState.push_back(new Knight(E_WHITE, this, {1,0}));
  m_currentState.push_back(new Knight(E_WHITE, this, {6,0}));
  // Creation of white Bishops
  m_currentState.push_back(new Bishop(E_WHITE, this, {2,0}));
  m_currentState.push_back(new Bishop(E_WHITE, this, {5,0}));
  // Creation of white Queen
  m_currentState.push_back(new Queen(E_WHITE, this, {3,0}));
  // Creation of white King
  m_currentState.push_back(new King(E_WHITE, this, {4,0}));
  // creation of white Pawns
  for (int w_counter = 0; w_counter < Constants::C_BOARD_WIDTH; w_counter++)
  {
      m_currentState.push_back(new Pawn(E_WHITE, this, {w_counter, 1}));
  }



  // Creation of black Rooks
  m_currentState.push_back(new Rook(E_BLACK, this, {0,7}));
  m_currentState.push_back(new Rook(E_BLACK, this, {7,7}));
  // Creation of black Knights
  m_currentState.push_back(new Knight(E_BLACK, this, {1,7}));
  m_currentState.push_back(new Knight(E_BLACK, this, {6,7}));
  // Creation of black Bishops
  m_currentState.push_back(new Bishop(E_BLACK, this, {2,7}));
  m_currentState.push_back(new Bishop(E_BLACK, this, {5,7}));
  // Creation of black Queen
  m_currentState.push_back(new Queen(E_BLACK, this, {3,7}));
  // Creation of black King
  m_currentState.push_back(new King(E_BLACK, this, {4,7}));
  // creation of black Pawns
  for (int w_counter = 0; w_counter < Constants::C_BOARD_WIDTH; w_counter++)
  {
      m_currentState.push_back(new Pawn(E_BLACK, this, {w_counter,6}));
  }
}

// Swap the player color to play
void Board::_swapPlayerColor()
{
  if (m_playerColor == E_WHITE)
  {
    m_playerColor = E_BLACK;
  }
  else
  {
    m_playerColor = E_WHITE;
  }
}

// Delete a piece from the square
void Board::_deletePiece(Piece * ai_deletedPiece)
{
  // If there is no Piece to delete
  if (ai_deletedPiece == nullptr)
  {
    return;
  }

  std::vector<Piece *>::iterator it_currentState = m_currentState.begin();

  for (; it_currentState != m_currentState.end(); it_currentState++)
  {
      if ( (*it_currentState)->getPosition() == ai_deletedPiece->getPosition())
      {
        delete *it_currentState;
        m_currentState.erase(it_currentState);
        return;
      }
  }
}

// Delete all pieces from the current state
void Board::_clearCurrentState()
{
  std::vector<Piece *>::iterator it_currentState = m_currentState.begin();

  for (; it_currentState != m_currentState.end(); it_currentState++)
  {
    delete *it_currentState;
  }

  m_currentState.clear();
  return;
}

// Check if the difference between to number is negatif or positif
int Board::_isDiffNeg(int w_endPos, int w_startPos)
{
  if ( (w_endPos - w_startPos) > 0)
  {
    return 1;
  }
  else if ( (w_endPos - w_startPos) < 0)
  {
    return -1;
  }
  else
  {
    return 0;
  }
}

// Return the number of square between 2 positions for bishop or rook or Queen
int Board::_numberOfSquareBetween(ts_position ai_startPosition, ts_position ai_endPosition)
{
  int w_numberOfSquare = abs(ai_startPosition.posX - ai_endPosition.posX);

  if ( w_numberOfSquare != 0)
  {
    return w_numberOfSquare;
  }
  else
  {
    return abs(ai_startPosition.posY - ai_endPosition.posY);
  }
}

// return the player color to play as a string
std::string Board::_getColorStr(ColorEnum ai_color)
{
  std::string w_colorPlayerStr = "";

  switch (ai_color)
  {
    case E_BLACK :
    {
      w_colorPlayerStr = "Black";
      break;
    }
    case E_WHITE :
    {
      w_colorPlayerStr = "White";
      break;
    }
    default :
    {
      TraceLog::logger.error(LOG_SOFT, "Player color Unknown ! Shouldn't happen !");
      w_colorPlayerStr = "Unknown";
      break;
    }
  }

  return w_colorPlayerStr;
}

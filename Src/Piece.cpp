#include "../Include/Piece.h"
#include "../Include/Constants.h"
#include "../Include/Board.h"
#include "../Include/Logger.h"


// Constructor
Piece::Piece(PieceEnum ai_name, ColorEnum ai_color, Board * ao_board, ts_position ai_position) : m_name(ai_name), m_color(ai_color), mp_mainBoard(ao_board)
{
  // We check the validity of the position
  if (_isInBoard(ai_position))
  {
    m_position = ai_position;
  }
  else // Otherwise the default value is used
  {
    TraceLog::logger.warning(LOG_SOFT, "Tried to create a piece out of the board : {%i,%i}. The piece is automatically set to {0,0}", ai_position.posX, ai_position.posY);
  }
}

// Destructor
Piece::~Piece()
{}

// Getter of piece position on the board
ts_position Piece::getPosition()
{
  return m_position;
}

// Setter of the piece position on the board
void Piece::setPosition(ts_position ai_position)
{
  // We check if the position is valid
  if ( _isInBoard(ai_position) )
  {
    m_position = ai_position;
  }
  else
  {
    TraceLog::logger.warning(LOG_SOFT, "Tried to set a position out of the board : {%i,%i}. ", ai_position.posX, ai_position.posY);
  }
}

// Getter of piece name
PieceEnum Piece::getName()
{
  return m_name;
}

// Getter of piece color
ColorEnum Piece::getColor()
{
  return m_color;
}

// Check if the position given is in the board boundaries
bool Piece::_isInBoard(ts_position ai_position)
{
  if ( (ai_position.posX >= 0) && (ai_position.posX < Constants::C_BOARD_WIDTH)
    && (ai_position.posY >= 0) && (ai_position.posY < Constants::C_BOARD_HEIGTH) )
  {
    return true;
  }
  else
  {
    return false;
  }
}

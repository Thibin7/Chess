#include "../Include/Queen.h"
#include "../Include/Board.h"

// Constructors
Queen::Queen(ColorEnum ai_color, Board * ao_board) : Piece(E_QUEEN, ai_color, ao_board)
{}

Queen::Queen(ColorEnum ai_color, Board * ao_board, ts_position ai_position) : Piece(E_QUEEN, ai_color, ao_board, ai_position)
{}

// Destructor
Queen::~Queen()
{}


// Display in the standard output the piece sprite
void Queen::displaySprite()
{
  if (m_color == E_WHITE)
  {
      std::cout << " \u265B ";
  }
  else
  {
      std::cout << " \u2655 ";
  }
}

// Check if the asked movement of the piece is valid
// [Warning] : only check the intrasec validity of movement, doesn't check
// the validity according to the other pieces positions
bool Queen::isMovementValid(ts_position ai_askedPosition)
{
  // If the position is the same, the movement is not valid
  if ( m_position == ai_askedPosition)
  {
    return false;
  }

  // If the position is out of the board the movement is not valid
  if ( !_isInBoard(ai_askedPosition) )
  {
    return false;
  }

  // If a piece is on the path
  if( mp_mainBoard->isPieceOnThePath(m_position, ai_askedPosition) )
  {
    return false;
  }

  // Used the Rook + Bishop guard
  if ( ( (m_position.posX == ai_askedPosition.posX)
    ||   (m_position.posY == ai_askedPosition.posY) )
    || ( abs(m_position.posX - ai_askedPosition.posX) == abs(m_position.posY - ai_askedPosition.posY) ))
  {
    return true;
  }
  else
  {
    return false;
  }
}

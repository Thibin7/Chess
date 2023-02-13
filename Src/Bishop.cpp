#include "../Include/Bishop.h"
#include "../Include/Board.h"

// Constructors
Bishop::Bishop(ColorEnum ai_color, Board * ao_board) : Piece(E_BISHOP, ai_color, ao_board)
{}

Bishop::Bishop(ColorEnum ai_color, Board * ao_board, ts_position ai_position) : Piece(E_BISHOP, ai_color, ao_board, ai_position)
{}

// Destructor
Bishop::~Bishop()
{}

// Display in the standard output the piece sprite
void Bishop::displaySprite()
{
  if (m_color == E_WHITE)
  {
      std::cout << " \u265D ";
  }
  else
  {
      std::cout << " \u2657 ";
  }
}

// Check if the asked movement of the piece is valid
// [Warning] : only check the intrasec validity of movement, doesn't check
// the validity according to the other pieces positions
bool Bishop::isMovementValid(ts_position ai_askedPosition)
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

  // If the diffence of deplecement on the 2 axes are the same it means we moved diagonaly
  // then the movement is valid
  if ( abs(m_position.posX - ai_askedPosition.posX) != abs(m_position.posY - ai_askedPosition.posY))
  {
    return false;
  }

  // If a piece is on the path
  if( mp_mainBoard->isPieceOnThePath(m_position, ai_askedPosition) )
  {
    return false;
  }

  return true;
}

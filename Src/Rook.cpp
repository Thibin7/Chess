#include "../Include/Rook.h"
#include "../Include/Board.h"

// Constructors
Rook::Rook(ColorEnum ai_color, Board * ao_board) : Piece(E_ROOK, ai_color, ao_board)
{}

Rook::Rook(ColorEnum ai_color, Board * ao_board, ts_position ai_position) : Piece(E_ROOK, ai_color, ao_board, ai_position)
{}

// Destructor
Rook::~Rook()
{}

// Display in the standard output the piece sprite
void Rook::displaySprite()
{
  if (m_color == E_WHITE)
  {
      std::cout << " \u265C ";
  }
  else
  {
      std::cout << " \u2656 ";
  }
}

// Check if the asked movement of the piece is valid
// [Warning] : only check the intrasec validity of movement, doesn't check
// the validity according to the other pieces positions
bool Rook::isMovementValid(ts_position ai_askedPosition)
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

  // If one of the axes hasn't moved it means we moved straight
  // then the movement is valid
  if ( (m_position.posX != ai_askedPosition.posX)
    && (m_position.posY != ai_askedPosition.posY))
  {
    return false;
  }


  // If a piece is on the path
  if( !mp_mainBoard->isPieceOnThePath(m_position, ai_askedPosition) )
  {
    return false;
  }

  return true;
}

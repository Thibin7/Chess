#include "../Include/King.h"

// Constructors
King::King(ColorEnum ai_color, Board * ao_board) : Piece(E_KING, ai_color, ao_board)
{}

King::King(ColorEnum ai_color, Board * ao_board, ts_position ai_position) : Piece(E_KING, ai_color, ao_board, ai_position)
{}

// Destructor
King::~King()
{}

// Display in the standard output the piece sprite
void King::displaySprite()
{
  if (m_color == E_WHITE)
  {
      std::cout << " \u265A ";
  }
  else
  {
      std::cout << " \u2654 ";
  }
}

// Check if the asked movement of the piece is valid
// [Warning] : only check the intrasec validity of movement, doesn't check
// the validity according to the other pieces positions
bool King::isMovementValid(ts_position ai_askedPosition)
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

  // If the difference between one of the axes is less than 2, it means we moved from 1 quare
  // then the movement is valid
  if ( abs(m_position.posX - ai_askedPosition.posX) < 2
    && abs(m_position.posY - ai_askedPosition.posY) < 2 )
  {
    return true;
  }
  else
  {
    return false;
  }
}

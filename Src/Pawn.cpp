#include "../Include/Pawn.h"
#include "../Include/Board.h"

// Constructors
Pawn::Pawn(ColorEnum ai_color, Board * ao_board) : Piece(E_PAWN, ai_color, ao_board)
{}

Pawn::Pawn(ColorEnum ai_color, Board * ao_board, ts_position ai_position) : Piece(E_PAWN, ai_color, ao_board, ai_position)
{}

// Destructor
Pawn::~Pawn()
{}

// Display in the standard output the piece sprite
void Pawn::displaySprite()
{
  if (m_color == E_WHITE)
  {
      std::cout << " \u265F ";
  }
  else
  {
      std::cout << " \u2659 ";
  }
}

// Check if the asked movement of the piece is valid
// [Warning] : only check the intrasec validity of movement, doesn't check
// the validity according to the other pieces positions
bool Pawn::isMovementValid(ts_position ai_askedPosition)
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

  // If the Piece is white
  if ( m_color == E_WHITE )
  {
    // If the piece is asked to move one square above it
    if ( ( (ai_askedPosition.posY - m_position.posY) == 1 )
       && ( ai_askedPosition.posX == m_position.posX ) )
    {
      return _moveOneSquare(ai_askedPosition);
    }
    // If the piece is asked to move 2 square up and never moved before
    else if ( ( (ai_askedPosition.posY - m_position.posY) == 2 )
           && ( ai_askedPosition.posX == m_position.posX ) )
    {
      return _moveTwoSquare(ai_askedPosition);
    }
    // If the pawn is asked to take a piece diagonnally
    else if( ( (ai_askedPosition.posY - m_position.posY) == 1)
          && (abs(ai_askedPosition.posX - m_position.posX) == 1) )
    {
      return _moveDiagonally(ai_askedPosition);
    }
    else // Movement not valid
    {
      return false;
    }
  }
  else // If the piece is black
  {
    // If the piece is asked to move on one of the 3 square under it
    if ( ( (m_position.posY - ai_askedPosition.posY) == 1 )
    &&  ( m_position.posX == ai_askedPosition.posX ) )
    {
      return _moveOneSquare(ai_askedPosition);
    }
    // If the piece is asked to move 2 square down and never moved before
    else if ( ( (m_position.posY - ai_askedPosition.posY) == 2 )
           && ( m_position.posX == ai_askedPosition.posX ) )
    {
      return _moveTwoSquare(ai_askedPosition);
    }
    // If the pawn is asked to take a piece diagonnally
    else if( ( (m_position.posY - ai_askedPosition.posY) == 1)
          && (abs(m_position.posX - ai_askedPosition.posX) == 1) )
    {
      return _moveDiagonally(ai_askedPosition);
    }
    else // Movement not valid
    {
      return false;
    }
  }
}

// Return true if the pawn can move one square up
bool Pawn::_moveOneSquare(ts_position ai_askedPosition)
{
    if (mp_mainBoard->isPieceOnSquare(ai_askedPosition) == nullptr)
    {
      return true;
    }
    else
    {
      return false;
    }
}

// Return true if the pawn can move two squares up
bool Pawn::_moveTwoSquare(ts_position ai_askedPosition)
{
  if ( (mp_mainBoard->isPieceOnSquare(ai_askedPosition) == nullptr)
     && !mp_mainBoard->isPieceOnThePath(m_position, ai_askedPosition)
     && !m_hasMoved )
  {
    m_hasMoved = true;
    return true;
  }
  else
  {
    return false;
  }
}

// Return true if the pawn can take the piece diagonnally
bool Pawn::_moveDiagonally(ts_position ai_askedPosition)
{
  Piece * w_targetTedPiece = mp_mainBoard->isPieceOnSquare(ai_askedPosition);
  if ( w_targetTedPiece != nullptr && w_targetTedPiece->getColor() != m_color)
  {
    return true;
  }
  else
  {
    return false;
  }
}

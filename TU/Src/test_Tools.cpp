#include "../Include/test_Tools.h"

#include <sstream>

#include "../../Include/Logger.h"
#include "../../Include/Constants.h"

// Check the default board configuration
void TestTools::_checkDefaultBoard(const std::string & ai_func, const unsigned int & ai_line, Board * ai_board)
{
  TraceLog::logger.info(LOG_TEST, "[%s : %i] Checking Default Board", ai_func.c_str(), ai_line);

  // Tab of the main pieces position at the start
  const PieceEnum w_pieceTab[8] = {E_ROOK, E_KNIGHT, E_BISHOP, E_QUEEN, E_KING, E_BISHOP, E_KNIGHT, E_ROOK};

  for ( int w_counter = 0; w_counter < 8; w_counter++)
  {
      ts_position w_whitePiecePosition = {w_counter,0};
      ts_position w_blackPiecePosition = {w_counter,7};

      // Check main piece position
      _checkPiece(__FUNCTION__, __LINE__, ai_board, w_whitePiecePosition, w_pieceTab[w_counter], E_WHITE);
      _checkPiece(__FUNCTION__, __LINE__, ai_board, w_blackPiecePosition, w_pieceTab[w_counter], E_BLACK);

      w_whitePiecePosition = {w_counter,1};
      w_blackPiecePosition = {w_counter,6};

      // Check pawn position
      _checkPiece(__FUNCTION__, __LINE__, ai_board, w_whitePiecePosition, E_PAWN, E_WHITE);
      _checkPiece(__FUNCTION__, __LINE__, ai_board, w_blackPiecePosition, E_PAWN, E_BLACK);
  }
}

// Check that the piece only make the movement allowed
void TestTools::_checkDefaultMovement(const std::string & ai_func,
                                      const unsigned int & ai_line,
                                      Board * ai_board,
                                      const std::string ai_filePath,
                                      const PieceEnum ai_pieceType,
                                      const ColorEnum ai_pieceColor,
                                      const ts_position ai_startPiecePosition,
                                      const std::vector<ts_position> ai_validPiecePosition)
{
  // To know the caller
  std::stringstream w_caller;
  w_caller << "[" << ai_func << ": " << ai_line << "]";
  TraceLog::logger.info(LOG_TEST, "Testing default movement : %s", w_caller.str().c_str());

  //Checking default knight movement
  for (int w_cntWidth = 0; w_cntWidth < Constants::C_BOARD_WIDTH; w_cntWidth++)
  {
    for (int w_cntHeight = 0; w_cntHeight < Constants::C_BOARD_HEIGTH; w_cntHeight++)
    {
        ts_position w_testedSquare = {w_cntWidth,w_cntHeight};
        ai_board->processMove( ai_startPiecePosition ,w_testedSquare);

        // If the move is valid for that piece
        if ( TestTools::isInVector<ts_position>(ai_validPiecePosition, w_testedSquare) )
        {
          TraceLog::logger.info(LOG_TEST, "Testing valid movement");
          _checkPiece(__FUNCTION__, __LINE__, ai_board, w_testedSquare, ai_pieceType, ai_pieceColor);
          _checkSquareEmpty(__FUNCTION__, __LINE__, ai_board, ai_startPiecePosition);

          // reload file
          ai_board->loadGameFile(ai_filePath);
        }
        else
        {
          TraceLog::logger.info(LOG_TEST, "Testing not valid movement");
          _checkPiece(__FUNCTION__, __LINE__, ai_board, ai_startPiecePosition, ai_pieceType, ai_pieceColor);
        }
    }
  }
}

// Check that piece cannot go on already taken square by same-color piece and out of the board squares
void TestTools::_checkBlockedMovement(const std::string & ai_func,
                                      const unsigned int & ai_line,
                                      Board * ai_board,
                                      const PieceEnum ai_pieceType,
                                      const ColorEnum ai_pieceColor,
                                      const ts_position ai_startPiecePosition,
                                      const std::vector<ts_position> ai_blockedSquares)
{
  // To know the caller
  std::stringstream w_caller;
  w_caller << "[" << ai_func << ": " << ai_line << "]";
  TraceLog::logger.info(LOG_TEST, "Testing blocked movement : %s", w_caller.str().c_str());

  //Checking default piece movement
  for (int w_cntWidth = -1; w_cntWidth < Constants::C_BOARD_WIDTH + 1; w_cntWidth++)
  {
    for (int w_cntHeight = -1; w_cntHeight < Constants::C_BOARD_HEIGTH + 1; w_cntHeight++)
    {
      ts_position w_testedSquare = {w_cntWidth,w_cntHeight};

      // If the square is a blocked one or if the square is out of board
      if ( TestTools::isInVector<ts_position>(ai_blockedSquares, w_testedSquare)  || (w_cntWidth < 0) || (w_cntHeight < 0))
      {
        ai_board->processMove( ai_startPiecePosition ,w_testedSquare);

        // Verifying that main piece doesn't moved
        TraceLog::logger.info(LOG_TEST, "Testing piece hasn't moved");
        _checkPiece(__FUNCTION__, __LINE__, ai_board, ai_startPiecePosition, ai_pieceType, ai_pieceColor);
      }

      // No need to load file again because movement should have been unvalid
    }
  }
}

// Check that piece can capture the other pieces
void TestTools::_checkCaptureMovement(const std::string & ai_func,
                                      const unsigned int & ai_line,
                                      Board * ai_board,
                                      const std::string ai_filePath,
                                      const PieceEnum ai_pieceType,
                                      const ColorEnum ai_pieceColor,
                                      const ts_position ai_startPiecePosition,
                                      const std::vector<ts_position> ai_otherPiecePosition)
{
  // To know the caller
  std::stringstream w_caller;
  w_caller << "[" << ai_func << ": " << ai_line << "]";
  TraceLog::logger.info(LOG_TEST, "Testing capture movement : %s", w_caller.str().c_str());

  std::vector<ts_position>::const_iterator w_pieceIt = ai_otherPiecePosition.begin();

  for (; w_pieceIt != ai_otherPiecePosition.end(); w_pieceIt++)
  {
      ai_board->processMove( ai_startPiecePosition , *w_pieceIt);

      _checkPiece(__FUNCTION__, __LINE__, ai_board, *w_pieceIt, ai_pieceType, ai_pieceColor);
      _checkSquareEmpty(__FUNCTION__, __LINE__, ai_board, ai_startPiecePosition);

      ai_board->loadGameFile(ai_filePath);
  }
}

// Check if the piece is the given type and color
void TestTools::_checkPiece(const std::string & ai_func, const unsigned int & ai_line, Board * ai_board, const ts_position ai_piecePosition, const PieceEnum& ai_pieceType, const ColorEnum& ai_pieceColor)
{
  // To know the caller
  std::stringstream w_caller;
  w_caller << "[" << ai_func << ": " << ai_line << "]";

  Piece * wp_piece = ai_board->isPieceOnSquare(ai_piecePosition);

  CPPUNIT_ASSERT_MESSAGE(w_caller.str() + " Piece exist ?", wp_piece != nullptr);
  CPPUNIT_ASSERT_EQUAL_MESSAGE(w_caller.str() + " Right Piece Type ?", wp_piece->getName(), ai_pieceType);
  CPPUNIT_ASSERT_EQUAL_MESSAGE(w_caller.str() + " Right Piece Color ?", wp_piece->getColor(), ai_pieceColor);
}

// Check if the square doesn't have a piece on it
void TestTools::_checkSquareEmpty(const std::string & ai_func, const unsigned int & ai_line, Board * ai_board, const ts_position ai_position)
{
  // To know the caller
  std::stringstream w_caller;
  w_caller << "[" << ai_func << ": " << ai_line << "]";

  Piece * wp_piece = ai_board->isPieceOnSquare(ai_position);

  CPPUNIT_ASSERT_MESSAGE(w_caller.str() + " Piece exist ?", wp_piece == nullptr);
}

// Check if the square have a piece on it
void TestTools::_checkSquareTaken(const std::string & ai_func, const unsigned int & ai_line, Board * ai_board, const ts_position ai_position)
{
  // To know the caller
  std::stringstream w_caller;
  w_caller << "[" << ai_func << ": " << ai_line << "]";

  Piece * wp_piece = ai_board->isPieceOnSquare(ai_position);

  CPPUNIT_ASSERT_MESSAGE(w_caller.str() + " Piece exist ?", wp_piece != nullptr);
}

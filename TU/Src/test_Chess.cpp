#include "../Include/test_Chess.h"
#include "../../Include/Piece.h"

CPPUNIT_TEST_SUITE_REGISTRATION(ChessTest);

ChessTest::ChessTest()
{}

void ChessTest::setUp()
{
  mp_board = new Board();
}

void ChessTest::tearDown()
{
  if (mp_board != nullptr)
  {
    delete mp_board;
  }
}

void ChessTest::test_knight()
{
  _checkDefaultBoard(__FUNCTION__, __LINE__);

  // Position of the 2 of the knight on the board
  ts_position w_whiteKnightPosition = {1,0};
  ts_position w_blackKnightPosition = {6,7};

  // First move [white knight] -> can move away from start square
  std::cout << "[TEST] [INFO] " << "[" << __FUNCTION__ << ": " << __LINE__ << "] " << "Checking Default Knight Move" << std::endl;
  mp_board->processMove( w_whiteKnightPosition ,{2,2});
  Piece * wp_knightPiece = mp_board->isPieceOnSquare({2,2});
  _checkPiece(__FUNCTION__, __LINE__, wp_knightPiece, E_KNIGHT, E_WHITE);
  w_whiteKnightPosition = {2,2}; // Update knight position

  // Second move [black knight] -> cannot move on a square were a black piece [black pawn] is
  // The knigt have to stay on his square and the blocking pawn should still be there
  std::cout << "[TEST] [INFO] " << "[" << __FUNCTION__ << ": " << __LINE__ << "] " << "Checking Knight blocked by same color piece" << std::endl;
  mp_board->processMove(w_blackKnightPosition,{4,6});
  wp_knightPiece = mp_board->isPieceOnSquare(w_blackKnightPosition);
  Piece * wp_pawnPiece = mp_board->isPieceOnSquare({4,6});
  _checkPiece(__FUNCTION__, __LINE__, wp_knightPiece, E_KNIGHT, E_BLACK);
  _checkPiece(__FUNCTION__, __LINE__, wp_pawnPiece, E_PAWN, E_BLACK);

  // Third move [black knight] -> cannot move if movement not valid
  std::cout << "[TEST] [INFO] " << "[" << __FUNCTION__ << ": " << __LINE__ << "] " << "Checking Knight invalid movement" << std::endl;
  mp_board->processMove(w_blackKnightPosition,{6,5});
  wp_knightPiece = mp_board->isPieceOnSquare(w_blackKnightPosition);
  _checkPiece(__FUNCTION__, __LINE__, wp_knightPiece, E_KNIGHT, E_BLACK);

  // Fourth move [black knight] -> cannot move if movement out of board
  std::cout << "[TEST] [INFO] " << "[" << __FUNCTION__ << ": " << __LINE__ << "] " << "Checking Knight out of bound movement" << std::endl;
  mp_board->processMove(w_blackKnightPosition,{7,9});
  wp_knightPiece = mp_board->isPieceOnSquare(w_blackKnightPosition);
  _checkPiece(__FUNCTION__, __LINE__, wp_knightPiece, E_KNIGHT, E_BLACK);

  // Fifth move [black and white knight] -> knight can "take" anothe piece -> test is blackKnight2 can take whiteknight1
  std::cout << "[TEST] [INFO] " << "[" << __FUNCTION__ << ": " << __LINE__ << "] " << "Checking Knight can take a piece" << std::endl;
  mp_board->processMove( w_blackKnightPosition ,{5,5});
  wp_knightPiece = mp_board->isPieceOnSquare({5,5});
  _checkPiece(__FUNCTION__, __LINE__, wp_knightPiece, E_KNIGHT, E_BLACK);
  w_blackKnightPosition = {5,5}; // Update knight position

  mp_board->processMove( w_whiteKnightPosition ,{4,3});
  wp_knightPiece = mp_board->isPieceOnSquare({4,3});
  _checkPiece(__FUNCTION__, __LINE__, wp_knightPiece, E_KNIGHT, E_WHITE);
  w_whiteKnightPosition = {4,3}; // Update knight position

  mp_board->processMove( w_blackKnightPosition ,{4,3});
  wp_knightPiece = mp_board->isPieceOnSquare({4,3});
  _checkPiece(__FUNCTION__, __LINE__, wp_knightPiece, E_KNIGHT, E_BLACK);
  w_blackKnightPosition = {4,3}; // Update knight position
}

void ChessTest::test_bishop()
{
  _checkDefaultBoard(__FUNCTION__, __LINE__);

  // Position of the 2 of the bishop on the board
  ts_position w_whiteBishopPosition = {2,0};
  ts_position w_blackBishopPosition = {2,7};

  // First move [white knight] -> can move away from start square
  std::cout << "[TEST] [INFO] " << "[" << __FUNCTION__ << ": " << __LINE__ << "] " << "Checking Default Bishop Move" << std::endl;
  mp_board->processMove({3,1},{3,3}); // Move away a blocking white pawn
  Piece * wp_pawnPiece = mp_board->isPieceOnSquare({3,3});
  _checkPiece(__FUNCTION__, __LINE__, wp_pawnPiece, E_PAWN, E_WHITE); // Pawn has been moved
  mp_board->processMove({1,6},{1,4}); // Move away a blocking black pawn
  wp_pawnPiece = mp_board->isPieceOnSquare({1,4});
  _checkPiece(__FUNCTION__, __LINE__, wp_pawnPiece, E_PAWN, E_BLACK); // Pawn has been moved

  mp_board->processMove( w_whiteBishopPosition ,{5,3});
  Piece * wp_bishopPiece = mp_board->isPieceOnSquare({5,3});
  _checkPiece(__FUNCTION__, __LINE__, wp_bishopPiece, E_BISHOP, E_WHITE);
  w_whiteBishopPosition = {5,3}; // Update bishop position

  // Second move [black bishop] -> cannot move on a square were a black piece [black pawn] is
  // The bishop have to stay on his square and the blocking pawn should still be there
  std::cout << "[TEST] [INFO] " << "[" << __FUNCTION__ << ": " << __LINE__ << "] " << "Checking bishop blocked by same color piece" << std::endl;
  mp_board->processMove(w_blackBishopPosition,{3,6});
  wp_bishopPiece = mp_board->isPieceOnSquare(w_blackBishopPosition);
  wp_pawnPiece = mp_board->isPieceOnSquare({3,6});
  _checkPiece(__FUNCTION__, __LINE__, wp_bishopPiece, E_BISHOP, E_BLACK);
  _checkPiece(__FUNCTION__, __LINE__, wp_pawnPiece, E_PAWN, E_BLACK);

  // Third move [black bishop] -> cannot move if movement not valid
  std::cout << "[TEST] [INFO] " << "[" << __FUNCTION__ << ": " << __LINE__ << "] " << "Checking Bishop invalid movement" << std::endl;
  mp_board->processMove(w_blackBishopPosition,{1,5});
  wp_bishopPiece = mp_board->isPieceOnSquare(w_blackBishopPosition);
  _checkPiece(__FUNCTION__, __LINE__, wp_bishopPiece, E_BISHOP, E_BLACK);

  // Fourth move [black knight] -> cannot move if movement out of board
  std::cout << "[TEST] [INFO] " << "[" << __FUNCTION__ << ": " << __LINE__ << "] " << "Checking Bishop out of bound movement" << std::endl;
  mp_board->processMove(w_blackBishopPosition,{3,8});
  wp_bishopPiece = mp_board->isPieceOnSquare(w_blackBishopPosition);
  _checkPiece(__FUNCTION__, __LINE__, wp_bishopPiece, E_BISHOP, E_BLACK);

  // Fifth move [black & white bishop] -> bishop can "take" another piece
  std::cout << "[TEST] [INFO] " << "[" << __FUNCTION__ << ": " << __LINE__ << "] " << "Checking Bishop can take a piece" << std::endl;
  mp_board->processMove( w_blackBishopPosition ,{0,5});
  wp_bishopPiece = mp_board->isPieceOnSquare({0,5});
  _checkPiece(__FUNCTION__, __LINE__, wp_bishopPiece, E_BISHOP, E_BLACK);
  w_blackBishopPosition = {0,5}; // Update bishop position

  // Checking there is actually a black piece on the square
  wp_pawnPiece = mp_board->isPieceOnSquare({2,6});
  _checkPiece(__FUNCTION__, __LINE__, wp_pawnPiece, E_PAWN, E_BLACK);

  // ove the white bishop on the same square
  mp_board->processMove( w_whiteBishopPosition ,{2,6});
  wp_bishopPiece = mp_board->isPieceOnSquare({2,6});
  _checkPiece(__FUNCTION__, __LINE__, wp_bishopPiece, E_BISHOP, E_WHITE);
  w_whiteBishopPosition = {4,1}; // Update bishop position
}

void ChessTest::test_rook()
{
  _checkDefaultBoard(__FUNCTION__, __LINE__);

  // Position of the 2 of the rook on the board
  ts_position w_whiteRookPosition = {7,0};
  ts_position w_blackRookPosition = {0,7};

  // First move [white knight] -> can move away from start square
  std::cout << "[TEST] [INFO] " << "[" << __FUNCTION__ << ": " << __LINE__ << "] " << "Checking Default Rook Move" << std::endl;
  mp_board->processMove({7,1},{7,3}); // Move away a blocking white pawn
  Piece * wp_pawnPiece = mp_board->isPieceOnSquare({7,3});
  _checkPiece(__FUNCTION__, __LINE__, wp_pawnPiece, E_PAWN, E_WHITE); // Pawn has been moved
  mp_board->processMove({0,6},{0,4}); // Move away a blocking black pawn
  wp_pawnPiece = mp_board->isPieceOnSquare({0,4});
  _checkPiece(__FUNCTION__, __LINE__, wp_pawnPiece, E_PAWN, E_BLACK); // Pawn has been moved

  mp_board->processMove( w_whiteRookPosition ,{7,2});
  Piece * wp_rookPiece = mp_board->isPieceOnSquare({7,2});
  _checkPiece(__FUNCTION__, __LINE__, wp_rookPiece, E_ROOK, E_WHITE);
  w_whiteRookPosition = {7,2}; // Update rook position

  // Second move [black rook] -> cannot move on a square were a black piece [black pawn] is
  // The rook have to stay on his square and the blocking pawn should still be there
  std::cout << "[TEST] [INFO] " << "[" << __FUNCTION__ << ": " << __LINE__ << "] " << "Checking rook blocked by same color piece" << std::endl;
  mp_board->processMove(w_blackRookPosition,{0,4});
  wp_rookPiece = mp_board->isPieceOnSquare(w_blackRookPosition);
  wp_pawnPiece = mp_board->isPieceOnSquare({0,4});
  _checkPiece(__FUNCTION__, __LINE__, wp_rookPiece, E_ROOK, E_BLACK);
  _checkPiece(__FUNCTION__, __LINE__, wp_pawnPiece, E_PAWN, E_BLACK);

  // Third move [black rook] -> cannot move if movement not valid
  std::cout << "[TEST] [INFO] " << "[" << __FUNCTION__ << ": " << __LINE__ << "] " << "Checking Rook invalid movement" << std::endl;
  mp_board->processMove(w_blackRookPosition,{1,5});
  wp_rookPiece = mp_board->isPieceOnSquare(w_blackRookPosition);
  _checkPiece(__FUNCTION__, __LINE__, wp_rookPiece, E_ROOK, E_BLACK);

  // Fourth move [black knight] -> cannot move if movement out of board
  std::cout << "[TEST] [INFO] " << "[" << __FUNCTION__ << ": " << __LINE__ << "] " << "Checking Rook out of bound movement" << std::endl;
  mp_board->processMove(w_blackRookPosition,{-1,7});
  wp_rookPiece = mp_board->isPieceOnSquare(w_blackRookPosition);
  _checkPiece(__FUNCTION__, __LINE__, wp_rookPiece, E_ROOK, E_BLACK);

  // Fifth move [black & white rook] -> rook can "take" another piece
  std::cout << "[TEST] [INFO] " << "[" << __FUNCTION__ << ": " << __LINE__ << "] " << "Checking Rook can take a piece" << std::endl;
  mp_board->processMove( w_blackRookPosition ,{0,5});
  wp_rookPiece = mp_board->isPieceOnSquare({0,5});
  _checkPiece(__FUNCTION__, __LINE__, wp_rookPiece, E_ROOK, E_BLACK);
  w_blackRookPosition = {0,5}; // Update rook position

  mp_board->processMove( w_whiteRookPosition ,{4,2});
  wp_rookPiece = mp_board->isPieceOnSquare({4,2});
  _checkPiece(__FUNCTION__, __LINE__, wp_rookPiece, E_ROOK, E_WHITE);
  w_whiteRookPosition = {4,2}; // Update rook position

  mp_board->processMove( w_blackRookPosition ,{4,5});
  wp_rookPiece = mp_board->isPieceOnSquare({4,5});
  _checkPiece(__FUNCTION__, __LINE__, wp_rookPiece, E_ROOK, E_BLACK);
  w_blackRookPosition = {4,5}; // Update rook position

  // Move the white rook on the same square
  mp_board->processMove( w_whiteRookPosition ,{4,5});
  wp_rookPiece = mp_board->isPieceOnSquare({4,5});
  _checkPiece(__FUNCTION__, __LINE__, wp_rookPiece, E_ROOK, E_WHITE);
  w_whiteRookPosition = {4,5}; // Update rook position
}

void ChessTest::test_king()
{
  _checkDefaultBoard(__FUNCTION__, __LINE__);

  // Position of the 2 of the king on the board
  ts_position w_whiteKingPosition = {4,0};
  ts_position w_blackKingPosition = {4,7};

  // First move [white knight] -> can move away from start square
  std::cout << "[TEST] [INFO] " << "[" << __FUNCTION__ << ": " << __LINE__ << "] " << "Checking Default King Move" << std::endl;
  mp_board->processMove({4,1},{4,3}); // Move away a blocking white pawn
  Piece * wp_pawnPiece = mp_board->isPieceOnSquare({4,3});
  _checkPiece(__FUNCTION__, __LINE__, wp_pawnPiece, E_PAWN, E_WHITE); // Pawn has been moved
  mp_board->processMove({4,6},{4,4}); // Move away a blocking black pawn
  wp_pawnPiece = mp_board->isPieceOnSquare({4,4});
  _checkPiece(__FUNCTION__, __LINE__, wp_pawnPiece, E_PAWN, E_BLACK); // Pawn has been moved

  mp_board->processMove( w_whiteKingPosition ,{4,1});
  Piece * wp_kingPiece = mp_board->isPieceOnSquare({4,1});
  _checkPiece(__FUNCTION__, __LINE__, wp_kingPiece, E_KING, E_WHITE);
  w_whiteKingPosition = {4,1}; // Update king position

  // Second move [black king] -> cannot move on a square were a black piece [black pawn] is
  // The king have to stay on his square and the blocking pawn should still be there
  std::cout << "[TEST] [INFO] " << "[" << __FUNCTION__ << ": " << __LINE__ << "] " << "Checking king blocked by same color piece" << std::endl;
  mp_board->processMove(w_blackKingPosition,{5,7});
  wp_kingPiece = mp_board->isPieceOnSquare(w_blackKingPosition);
  wp_pawnPiece = mp_board->isPieceOnSquare({5,7});
  _checkPiece(__FUNCTION__, __LINE__, wp_kingPiece, E_KING, E_BLACK);
  _checkPiece(__FUNCTION__, __LINE__, wp_pawnPiece, E_BISHOP, E_BLACK);

  // Third move [black king] -> cannot move if movement not valid
  std::cout << "[TEST] [INFO] " << "[" << __FUNCTION__ << ": " << __LINE__ << "] " << "Checking King invalid movement" << std::endl;
  mp_board->processMove(w_blackKingPosition,{4,5}); // Invalid movement
  wp_kingPiece = mp_board->isPieceOnSquare(w_blackKingPosition);
  _checkPiece(__FUNCTION__, __LINE__, wp_kingPiece, E_KING, E_BLACK);

  // Fourth move [black knight] -> cannot move if movement out of board
  std::cout << "[TEST] [INFO] " << "[" << __FUNCTION__ << ": " << __LINE__ << "] " << "Checking King out of bound movement" << std::endl;
  mp_board->processMove(w_blackKingPosition,{4,8});
  wp_kingPiece = mp_board->isPieceOnSquare(w_blackKingPosition);
  _checkPiece(__FUNCTION__, __LINE__, wp_kingPiece, E_KING, E_BLACK);

  // Fifth move [black & white king] -> king can "take" another piece
  std::cout << "[TEST] [INFO] " << "[" << __FUNCTION__ << ": " << __LINE__ << "] " << "Checking King can take a piece" << std::endl;
  mp_board->processMove( {5,7} ,{1,3}); // Move bishop
  Piece * wp_bishopPiece = mp_board->isPieceOnSquare({1,3});
  _checkPiece(__FUNCTION__, __LINE__, wp_bishopPiece, E_BISHOP, E_BLACK);

  mp_board->processMove( w_whiteKingPosition ,{3,2});
  wp_kingPiece = mp_board->isPieceOnSquare({3,2});
  _checkPiece(__FUNCTION__, __LINE__, wp_kingPiece, E_KING, E_WHITE);
  w_whiteKingPosition = {3,2}; // Update king position

  mp_board->processMove( {1,3} ,{2,2}); // Move bishop
  wp_bishopPiece = mp_board->isPieceOnSquare({2,2});
  _checkPiece(__FUNCTION__, __LINE__, wp_bishopPiece, E_BISHOP, E_BLACK);

  mp_board->processMove( w_whiteKingPosition ,{2,2});
  wp_kingPiece = mp_board->isPieceOnSquare({2,2});
  _checkPiece(__FUNCTION__, __LINE__, wp_kingPiece, E_KING, E_WHITE);
  w_blackKingPosition = {2,2}; // Update king position
}

// Check the default board configuration
void ChessTest::_checkDefaultBoard(const std::string & ai_func, const unsigned int & ai_line)
{
  std::cout << "[TEST] [INFO] " << "[" << ai_func << ": " << ai_line << "] " << "Checking Default Board" << std::endl;

  // Tab of the main pieces position at the start
  const PieceEnum w_pieceTab[8] = {E_ROOK, E_KNIGHT, E_BISHOP, E_QUEEN, E_KING, E_BISHOP, E_KNIGHT, E_ROOK};

  for ( int w_counter = 0; w_counter < 8; w_counter++)
  {
      Piece * wp_whitePiece = mp_board->isPieceOnSquare({w_counter,0});
      Piece * wp_blackPiece = mp_board->isPieceOnSquare({w_counter,7});

      // Check main piece position
      _checkPiece(__FUNCTION__, __LINE__, wp_whitePiece, w_pieceTab[w_counter], E_WHITE);
      _checkPiece(__FUNCTION__, __LINE__, wp_blackPiece, w_pieceTab[w_counter], E_BLACK);


      wp_whitePiece = mp_board->isPieceOnSquare({w_counter,1});
      wp_blackPiece = mp_board->isPieceOnSquare({w_counter,6});

      // Check pawn position
      _checkPiece(__FUNCTION__, __LINE__, wp_whitePiece, E_PAWN, E_WHITE);
      _checkPiece(__FUNCTION__, __LINE__, wp_blackPiece, E_PAWN, E_BLACK);
  }
}

// Check if the piece is the given type and color
void ChessTest::_checkPiece(const std::string & ai_func, const unsigned int & ai_line, Piece * ai_piece, const PieceEnum& ai_pieceType, const ColorEnum& ai_pieceColor)
{
  // To know the caller
  std::stringstream w_caller;
  w_caller << "[" << ai_func << ": " << ai_line << "]";

  CPPUNIT_ASSERT_MESSAGE(w_caller.str() + " Piece exist ?", ai_piece != nullptr);
  CPPUNIT_ASSERT_EQUAL_MESSAGE(w_caller.str() + " Right Piece Type ?", ai_piece->getName(),ai_pieceType);
  CPPUNIT_ASSERT_EQUAL_MESSAGE(w_caller.str() + " Right Piece Color ?", ai_piece->getColor(), ai_pieceColor);
}

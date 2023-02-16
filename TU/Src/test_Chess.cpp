#include "../Include/test_Chess.h"
#include "../Include/test_Tools.h"
#include "../../Include/Piece.h"
#include "../../Include/Constants.h"

const std::string C_KNIGHT_DEFAULT_MOV_FILE_PATH = "./parameters/test_knight_default_movement.txt";
const std::string C_KNIGHT_BLOCKED_MOV_FILE_PATH = "./parameters/test_knight_blocked_movement.txt";
const std::string C_KNIGHT_CAPTURE_FILE_PATH     = "./parameters/test_knight_capture.txt";

CPPUNIT_TEST_SUITE_REGISTRATION(ChessTest);

ChessTest::ChessTest()
{}

void ChessTest::setUp()
{}

void ChessTest::_setup(std::string w_filePath)
{
  mp_board = new Board(w_filePath);
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
  _setup(C_KNIGHT_DEFAULT_MOV_FILE_PATH);


  // STEP 1
  const ts_position C_KNIGHT_POS_DEFAULT_MOV = {3,4}; // Knight position on the file C_KNIGHT_DEFAULT_MOV_FILE_PATH
  const std::vector<ts_position> C_VEC_VALID_KNIGHT_MOVE{{4,6},{5,5},{5,3},{4,2},{2,2},{1,3},{1,5},{2,6}}; // All valid move for the knight
  _checkPiece(__FUNCTION__, __LINE__, C_KNIGHT_POS_DEFAULT_MOV, E_KNIGHT, E_WHITE); // Check if file correctly loaded


  //Checking default knight movement
  _checkDefaultMovement(__FUNCTION__, __LINE__, C_KNIGHT_DEFAULT_MOV_FILE_PATH, E_KNIGHT, E_WHITE, C_KNIGHT_POS_DEFAULT_MOV, C_VEC_VALID_KNIGHT_MOVE);


  // STEP 2
  const ts_position C_KNIGHT_POS_MAIN  = {2,6};  // Main knight position we want to test on the file C_KNIGHT_BLOCKED_MOV_FILE_PATH
  const ts_position C_KNIGHT_POS_OTHER = {0,5};  // Other knight position on the file C_KNIGHT_BLOCKED_MOV_FILE_PATH
  const ts_position C_PAWN_POS         = {0,7};  // Pawn position on the file C_KNIGHT_BLOCKED_MOV_FILE_PATH
  const ts_position C_KING_POS         = {4,7};  // King position on the file C_KNIGHT_BLOCKED_MOV_FILE_PATH
  const ts_position C_QUEEN_POS        = {4,5};  // Queen position on the file C_KNIGHT_BLOCKED_MOV_FILE_PATH
  const ts_position C_ROOK_POS         = {1,4};  // Rook position on the file C_KNIGHT_BLOCKED_MOV_FILE_PATH
  const ts_position C_BISHOP_POS       = {3,4};  // Bishop position on the file C_KNIGHT_BLOCKED_MOV_FILE_PATH

  // Vector of all piece position (except main Knight)
  const std::vector<ts_position> C_OTHER_PIECE_POSITION {C_KNIGHT_POS_MAIN,
                                                            C_KNIGHT_POS_OTHER ,
                                                             C_PAWN_POS,
                                                             C_KING_POS,
                                                             C_QUEEN_POS,
                                                             C_ROOK_POS,
                                                             C_BISHOP_POS};

  // Loading test file
  mp_board->loadGameFile(C_KNIGHT_BLOCKED_MOV_FILE_PATH);

  // Check if file correctly loaded
  _checkPiece(__FUNCTION__, __LINE__, C_KNIGHT_POS_MAIN, E_KNIGHT, E_BLACK);
  _checkPiece(__FUNCTION__, __LINE__, C_KNIGHT_POS_OTHER, E_KNIGHT, E_BLACK);
  _checkPiece(__FUNCTION__, __LINE__, C_PAWN_POS, E_PAWN, E_BLACK);
  _checkPiece(__FUNCTION__, __LINE__, C_KING_POS, E_KING, E_BLACK);
  _checkPiece(__FUNCTION__, __LINE__, C_QUEEN_POS, E_QUEEN, E_BLACK);
  _checkPiece(__FUNCTION__, __LINE__, C_ROOK_POS, E_ROOK, E_BLACK);
  _checkPiece(__FUNCTION__, __LINE__, C_BISHOP_POS, E_BISHOP, E_BLACK);

  //Checking default knight movement
  _checkBlockedMovement(__FUNCTION__, __LINE__, E_KNIGHT, E_BLACK, C_KNIGHT_POS_MAIN, C_OTHER_PIECE_POSITION);


  // STEP 3
  const ts_position C_WHITE_KNIGHT_POS = {3,4};  // Main knight position we want to test on the file C_KNIGHT_CAPTURE_FILE_PATH
  const ts_position C_BLACK_KNIGHT_POS = {4,6};  // Other knight position on the file C_KNIGHT_CAPTURE_FILE_PATH
  const ts_position C_BLACK_PAWN_POS   = {4,2};  // Pawn position on the file C_KNIGHT_CAPTURE_FILE_PATH
  const ts_position C_BLACK_QUEEN_POS  = {5,3};  // Queen position on the file C_KNIGHT_CAPTURE_FILE_PATH
  const ts_position C_BLACK_ROOK_POS   = {2,6};  // Rook position on the file C_KNIGHT_CAPTURE_FILE_PATH
  const ts_position C_BLACK_BISHOP_POS = {5,5};  // Bishop position on the file C_KNIGHT_CAPTURE_FILE_PATH

  // Vector of all piece position (except main Knight)
  const std::vector<ts_position> C_WHITE_PIECE_POSITION {C_WHITE_KNIGHT_POS,
                                                        C_BLACK_KNIGHT_POS ,
                                                        C_BLACK_PAWN_POS,
                                                        C_BLACK_QUEEN_POS,
                                                        C_BLACK_ROOK_POS,
                                                        C_BLACK_BISHOP_POS};

  // Loading test file
  mp_board->loadGameFile(C_KNIGHT_CAPTURE_FILE_PATH);

  // Check if file correctly loaded
  _checkPiece(__FUNCTION__, __LINE__, C_WHITE_KNIGHT_POS, E_KNIGHT, E_WHITE);
  _checkPiece(__FUNCTION__, __LINE__, C_BLACK_KNIGHT_POS, E_KNIGHT, E_BLACK);
  _checkPiece(__FUNCTION__, __LINE__, C_BLACK_PAWN_POS, E_PAWN, E_BLACK);
  _checkPiece(__FUNCTION__, __LINE__, C_BLACK_QUEEN_POS, E_QUEEN, E_BLACK);
  _checkPiece(__FUNCTION__, __LINE__, C_BLACK_ROOK_POS, E_ROOK, E_BLACK);
  _checkPiece(__FUNCTION__, __LINE__, C_BLACK_BISHOP_POS, E_BISHOP, E_BLACK);



  // // Position of the 2 of the knight on the board
  // ts_position w_whiteKnightPosition = {1,0};
  // ts_position w_blackKnightPosition = {6,7};
  //
  // // First move [white knight] -> can move away from start square
  // std::cout << "[TEST] [INFO] " << "[" << __FUNCTION__ << ": " << __LINE__ << "] " << "Checking Default Knight Move" << std::endl;
  // mp_board->processMove( w_whiteKnightPosition ,{2,2});
  // Piece * wp_knightPiece = mp_board->isPieceOnSquare({2,2});
  // _checkPiece(__FUNCTION__, __LINE__, wp_knightPiece, E_KNIGHT, E_WHITE);
  // w_whiteKnightPosition = {2,2}; // Update knight position
  //
  // // Second move [black knight] -> cannot move on a square were a black piece [black pawn] is
  // // The knigt have to stay on his square and the blocking pawn should still be there
  // std::cout << "[TEST] [INFO] " << "[" << __FUNCTION__ << ": " << __LINE__ << "] " << "Checking Knight blocked by same color piece" << std::endl;
  // mp_board->processMove(w_blackKnightPosition,{4,6});
  // wp_knightPiece = mp_board->isPieceOnSquare(w_blackKnightPosition);
  // Piece * wp_pawnPiece = mp_board->isPieceOnSquare({4,6});
  // _checkPiece(__FUNCTION__, __LINE__, wp_knightPiece, E_KNIGHT, E_BLACK);
  // _checkPiece(__FUNCTION__, __LINE__, wp_pawnPiece, E_PAWN, E_BLACK);
  //
  // // Third move [black knight] -> cannot move if movement not valid
  // std::cout << "[TEST] [INFO] " << "[" << __FUNCTION__ << ": " << __LINE__ << "] " << "Checking Knight invalid movement" << std::endl;
  // mp_board->processMove(w_blackKnightPosition,{6,5});
  // wp_knightPiece = mp_board->isPieceOnSquare(w_blackKnightPosition);
  // _checkPiece(__FUNCTION__, __LINE__, wp_knightPiece, E_KNIGHT, E_BLACK);
  //
  // // Fourth move [black knight] -> cannot move if movement out of board
  // std::cout << "[TEST] [INFO] " << "[" << __FUNCTION__ << ": " << __LINE__ << "] " << "Checking Knight out of bound movement" << std::endl;
  // mp_board->processMove(w_blackKnightPosition,{7,9});
  // wp_knightPiece = mp_board->isPieceOnSquare(w_blackKnightPosition);
  // _checkPiece(__FUNCTION__, __LINE__, wp_knightPiece, E_KNIGHT, E_BLACK);
  //
  // // Fifth move [black and white knight] -> knight can "take" anothe piece -> test is blackKnight2 can take whiteknight1
  // std::cout << "[TEST] [INFO] " << "[" << __FUNCTION__ << ": " << __LINE__ << "] " << "Checking Knight can take a piece" << std::endl;
  // mp_board->processMove( w_blackKnightPosition ,{5,5});
  // wp_knightPiece = mp_board->isPieceOnSquare({5,5});
  // _checkPiece(__FUNCTION__, __LINE__, wp_knightPiece, E_KNIGHT, E_BLACK);
  // w_blackKnightPosition = {5,5}; // Update knight position
  //
  // mp_board->processMove( w_whiteKnightPosition ,{4,3});
  // wp_knightPiece = mp_board->isPieceOnSquare({4,3});
  // _checkPiece(__FUNCTION__, __LINE__, wp_knightPiece, E_KNIGHT, E_WHITE);
  // w_whiteKnightPosition = {4,3}; // Update knight position
  //
  // mp_board->processMove( w_blackKnightPosition ,{4,3});
  // wp_knightPiece = mp_board->isPieceOnSquare({4,3});
  // _checkPiece(__FUNCTION__, __LINE__, wp_knightPiece, E_KNIGHT, E_BLACK);
  // w_blackKnightPosition = {4,3}; // Update knight position
}

void ChessTest::test_bishop()
{
  // _checkDefaultBoard(__FUNCTION__, __LINE__);
  //
  // // Position of the 2 of the bishop on the board
  // ts_position w_whiteBishopPosition = {2,0};
  // ts_position w_blackBishopPosition = {2,7};
  //
  // // First move [white knight] -> can move away from start square
  // std::cout << "[TEST] [INFO] " << "[" << __FUNCTION__ << ": " << __LINE__ << "] " << "Checking Default Bishop Move" << std::endl;
  // mp_board->processMove({3,1},{3,3}); // Move away a blocking white pawn
  // Piece * wp_pawnPiece = mp_board->isPieceOnSquare({3,3});
  // _checkPiece(__FUNCTION__, __LINE__, wp_pawnPiece, E_PAWN, E_WHITE); // Pawn has been moved
  // mp_board->processMove({1,6},{1,4}); // Move away a blocking black pawn
  // wp_pawnPiece = mp_board->isPieceOnSquare({1,4});
  // _checkPiece(__FUNCTION__, __LINE__, wp_pawnPiece, E_PAWN, E_BLACK); // Pawn has been moved
  //
  // mp_board->processMove( w_whiteBishopPosition ,{5,3});
  // Piece * wp_bishopPiece = mp_board->isPieceOnSquare({5,3});
  // _checkPiece(__FUNCTION__, __LINE__, wp_bishopPiece, E_BISHOP, E_WHITE);
  // w_whiteBishopPosition = {5,3}; // Update bishop position
  //
  // // Second move [black bishop] -> cannot move on a square were a black piece [black pawn] is
  // // The bishop have to stay on his square and the blocking pawn should still be there
  // std::cout << "[TEST] [INFO] " << "[" << __FUNCTION__ << ": " << __LINE__ << "] " << "Checking bishop blocked by same color piece" << std::endl;
  // mp_board->processMove(w_blackBishopPosition,{3,6});
  // wp_bishopPiece = mp_board->isPieceOnSquare(w_blackBishopPosition);
  // wp_pawnPiece = mp_board->isPieceOnSquare({3,6});
  // _checkPiece(__FUNCTION__, __LINE__, wp_bishopPiece, E_BISHOP, E_BLACK);
  // _checkPiece(__FUNCTION__, __LINE__, wp_pawnPiece, E_PAWN, E_BLACK);
  //
  // // Third move [black bishop] -> cannot move if movement not valid
  // std::cout << "[TEST] [INFO] " << "[" << __FUNCTION__ << ": " << __LINE__ << "] " << "Checking Bishop invalid movement" << std::endl;
  // mp_board->processMove(w_blackBishopPosition,{1,5});
  // wp_bishopPiece = mp_board->isPieceOnSquare(w_blackBishopPosition);
  // _checkPiece(__FUNCTION__, __LINE__, wp_bishopPiece, E_BISHOP, E_BLACK);
  //
  // // Fourth move [black knight] -> cannot move if movement out of board
  // std::cout << "[TEST] [INFO] " << "[" << __FUNCTION__ << ": " << __LINE__ << "] " << "Checking Bishop out of bound movement" << std::endl;
  // mp_board->processMove(w_blackBishopPosition,{3,8});
  // wp_bishopPiece = mp_board->isPieceOnSquare(w_blackBishopPosition);
  // _checkPiece(__FUNCTION__, __LINE__, wp_bishopPiece, E_BISHOP, E_BLACK);
  //
  // // Fifth move [black & white bishop] -> bishop can "take" another piece
  // std::cout << "[TEST] [INFO] " << "[" << __FUNCTION__ << ": " << __LINE__ << "] " << "Checking Bishop can take a piece" << std::endl;
  // mp_board->processMove( w_blackBishopPosition ,{0,5});
  // wp_bishopPiece = mp_board->isPieceOnSquare({0,5});
  // _checkPiece(__FUNCTION__, __LINE__, wp_bishopPiece, E_BISHOP, E_BLACK);
  // w_blackBishopPosition = {0,5}; // Update bishop position
  //
  // // Checking there is actually a black piece on the square
  // wp_pawnPiece = mp_board->isPieceOnSquare({2,6});
  // _checkPiece(__FUNCTION__, __LINE__, wp_pawnPiece, E_PAWN, E_BLACK);
  //
  // // ove the white bishop on the same square
  // mp_board->processMove( w_whiteBishopPosition ,{2,6});
  // wp_bishopPiece = mp_board->isPieceOnSquare({2,6});
  // _checkPiece(__FUNCTION__, __LINE__, wp_bishopPiece, E_BISHOP, E_WHITE);
  // w_whiteBishopPosition = {4,1}; // Update bishop position
}

void ChessTest::test_rook()
{
  // _checkDefaultBoard(__FUNCTION__, __LINE__);
  //
  // // Position of the 2 of the rook on the board
  // ts_position w_whiteRookPosition = {7,0};
  // ts_position w_blackRookPosition = {0,7};
  //
  // // First move [white knight] -> can move away from start square
  // std::cout << "[TEST] [INFO] " << "[" << __FUNCTION__ << ": " << __LINE__ << "] " << "Checking Default Rook Move" << std::endl;
  // mp_board->processMove({7,1},{7,3}); // Move away a blocking white pawn
  // Piece * wp_pawnPiece = mp_board->isPieceOnSquare({7,3});
  // _checkPiece(__FUNCTION__, __LINE__, wp_pawnPiece, E_PAWN, E_WHITE); // Pawn has been moved
  // mp_board->processMove({0,6},{0,4}); // Move away a blocking black pawn
  // wp_pawnPiece = mp_board->isPieceOnSquare({0,4});
  // _checkPiece(__FUNCTION__, __LINE__, wp_pawnPiece, E_PAWN, E_BLACK); // Pawn has been moved
  //
  // mp_board->processMove( w_whiteRookPosition ,{7,2});
  // Piece * wp_rookPiece = mp_board->isPieceOnSquare({7,2});
  // _checkPiece(__FUNCTION__, __LINE__, wp_rookPiece, E_ROOK, E_WHITE);
  // w_whiteRookPosition = {7,2}; // Update rook position
  //
  // // Second move [black rook] -> cannot move on a square were a black piece [black pawn] is
  // // The rook have to stay on his square and the blocking pawn should still be there
  // std::cout << "[TEST] [INFO] " << "[" << __FUNCTION__ << ": " << __LINE__ << "] " << "Checking rook blocked by same color piece" << std::endl;
  // mp_board->processMove(w_blackRookPosition,{0,4});
  // wp_rookPiece = mp_board->isPieceOnSquare(w_blackRookPosition);
  // wp_pawnPiece = mp_board->isPieceOnSquare({0,4});
  // _checkPiece(__FUNCTION__, __LINE__, wp_rookPiece, E_ROOK, E_BLACK);
  // _checkPiece(__FUNCTION__, __LINE__, wp_pawnPiece, E_PAWN, E_BLACK);
  //
  // // Third move [black rook] -> cannot move if movement not valid
  // std::cout << "[TEST] [INFO] " << "[" << __FUNCTION__ << ": " << __LINE__ << "] " << "Checking Rook invalid movement" << std::endl;
  // mp_board->processMove(w_blackRookPosition,{1,5});
  // wp_rookPiece = mp_board->isPieceOnSquare(w_blackRookPosition);
  // _checkPiece(__FUNCTION__, __LINE__, wp_rookPiece, E_ROOK, E_BLACK);
  //
  // // Fourth move [black knight] -> cannot move if movement out of board
  // std::cout << "[TEST] [INFO] " << "[" << __FUNCTION__ << ": " << __LINE__ << "] " << "Checking Rook out of bound movement" << std::endl;
  // mp_board->processMove(w_blackRookPosition,{-1,7});
  // wp_rookPiece = mp_board->isPieceOnSquare(w_blackRookPosition);
  // _checkPiece(__FUNCTION__, __LINE__, wp_rookPiece, E_ROOK, E_BLACK);
  //
  // // Fifth move [black & white rook] -> rook can "take" another piece
  // std::cout << "[TEST] [INFO] " << "[" << __FUNCTION__ << ": " << __LINE__ << "] " << "Checking Rook can take a piece" << std::endl;
  // mp_board->processMove( w_blackRookPosition ,{0,5});
  // wp_rookPiece = mp_board->isPieceOnSquare({0,5});
  // _checkPiece(__FUNCTION__, __LINE__, wp_rookPiece, E_ROOK, E_BLACK);
  // w_blackRookPosition = {0,5}; // Update rook position
  //
  // mp_board->processMove( w_whiteRookPosition ,{4,2});
  // wp_rookPiece = mp_board->isPieceOnSquare({4,2});
  // _checkPiece(__FUNCTION__, __LINE__, wp_rookPiece, E_ROOK, E_WHITE);
  // w_whiteRookPosition = {4,2}; // Update rook position
  //
  // mp_board->processMove( w_blackRookPosition ,{4,5});
  // wp_rookPiece = mp_board->isPieceOnSquare({4,5});
  // _checkPiece(__FUNCTION__, __LINE__, wp_rookPiece, E_ROOK, E_BLACK);
  // w_blackRookPosition = {4,5}; // Update rook position
  //
  // // Move the white rook on the same square
  // mp_board->processMove( w_whiteRookPosition ,{4,5});
  // wp_rookPiece = mp_board->isPieceOnSquare({4,5});
  // _checkPiece(__FUNCTION__, __LINE__, wp_rookPiece, E_ROOK, E_WHITE);
  // w_whiteRookPosition = {4,5}; // Update rook position
}

void ChessTest::test_king()
{
  // _checkDefaultBoard(__FUNCTION__, __LINE__);
  //
  // // Position of the 2 of the king on the board
  // ts_position w_whiteKingPosition = {4,0};
  // ts_position w_blackKingPosition = {4,7};
  //
  // // First move [white knight] -> can move away from start square
  // std::cout << "[TEST] [INFO] " << "[" << __FUNCTION__ << ": " << __LINE__ << "] " << "Checking Default King Move" << std::endl;
  // mp_board->processMove({4,1},{4,3}); // Move away a blocking white pawn
  // Piece * wp_pawnPiece = mp_board->isPieceOnSquare({4,3});
  // _checkPiece(__FUNCTION__, __LINE__, wp_pawnPiece, E_PAWN, E_WHITE); // Pawn has been moved
  // mp_board->processMove({4,6},{4,4}); // Move away a blocking black pawn
  // wp_pawnPiece = mp_board->isPieceOnSquare({4,4});
  // _checkPiece(__FUNCTION__, __LINE__, wp_pawnPiece, E_PAWN, E_BLACK); // Pawn has been moved
  //
  // mp_board->processMove( w_whiteKingPosition ,{4,1});
  // Piece * wp_kingPiece = mp_board->isPieceOnSquare({4,1});
  // _checkPiece(__FUNCTION__, __LINE__, wp_kingPiece, E_KING, E_WHITE);
  // w_whiteKingPosition = {4,1}; // Update king position
  //
  // // Second move [black king] -> cannot move on a square were a black piece [black pawn] is
  // // The king have to stay on his square and the blocking pawn should still be there
  // std::cout << "[TEST] [INFO] " << "[" << __FUNCTION__ << ": " << __LINE__ << "] " << "Checking king blocked by same color piece" << std::endl;
  // mp_board->processMove(w_blackKingPosition,{5,7});
  // wp_kingPiece = mp_board->isPieceOnSquare(w_blackKingPosition);
  // wp_pawnPiece = mp_board->isPieceOnSquare({5,7});
  // _checkPiece(__FUNCTION__, __LINE__, wp_kingPiece, E_KING, E_BLACK);
  // _checkPiece(__FUNCTION__, __LINE__, wp_pawnPiece, E_BISHOP, E_BLACK);
  //
  // // Third move [black king] -> cannot move if movement not valid
  // std::cout << "[TEST] [INFO] " << "[" << __FUNCTION__ << ": " << __LINE__ << "] " << "Checking King invalid movement" << std::endl;
  // mp_board->processMove(w_blackKingPosition,{4,5}); // Invalid movement
  // wp_kingPiece = mp_board->isPieceOnSquare(w_blackKingPosition);
  // _checkPiece(__FUNCTION__, __LINE__, wp_kingPiece, E_KING, E_BLACK);
  //
  // // Fourth move [black knight] -> cannot move if movement out of board
  // std::cout << "[TEST] [INFO] " << "[" << __FUNCTION__ << ": " << __LINE__ << "] " << "Checking King out of bound movement" << std::endl;
  // mp_board->processMove(w_blackKingPosition,{4,8});
  // wp_kingPiece = mp_board->isPieceOnSquare(w_blackKingPosition);
  // _checkPiece(__FUNCTION__, __LINE__, wp_kingPiece, E_KING, E_BLACK);
  //
  // // Fifth move [black & white king] -> king can "take" another piece
  // std::cout << "[TEST] [INFO] " << "[" << __FUNCTION__ << ": " << __LINE__ << "] " << "Checking King can take a piece" << std::endl;
  // mp_board->processMove( {5,7} ,{1,3}); // Move bishop
  // Piece * wp_bishopPiece = mp_board->isPieceOnSquare({1,3});
  // _checkPiece(__FUNCTION__, __LINE__, wp_bishopPiece, E_BISHOP, E_BLACK);
  //
  // mp_board->processMove( w_whiteKingPosition ,{3,2});
  // wp_kingPiece = mp_board->isPieceOnSquare({3,2});
  // _checkPiece(__FUNCTION__, __LINE__, wp_kingPiece, E_KING, E_WHITE);
  // w_whiteKingPosition = {3,2}; // Update king position
  //
  // mp_board->processMove( {1,3} ,{2,2}); // Move bishop
  // wp_bishopPiece = mp_board->isPieceOnSquare({2,2});
  // _checkPiece(__FUNCTION__, __LINE__, wp_bishopPiece, E_BISHOP, E_BLACK);
  //
  // mp_board->processMove( w_whiteKingPosition ,{2,2});
  // wp_kingPiece = mp_board->isPieceOnSquare({2,2});
  // _checkPiece(__FUNCTION__, __LINE__, wp_kingPiece, E_KING, E_WHITE);
  // w_blackKingPosition = {2,2}; // Update king position
}

// Check the default board configuration
void ChessTest::_checkDefaultBoard(const std::string & ai_func, const unsigned int & ai_line)
{
  std::cout << "[TEST] [INFO] " << "[" << ai_func << ": " << ai_line << "] " << "Checking Default Board" << std::endl;

  // Tab of the main pieces position at the start
  const PieceEnum w_pieceTab[8] = {E_ROOK, E_KNIGHT, E_BISHOP, E_QUEEN, E_KING, E_BISHOP, E_KNIGHT, E_ROOK};

  for ( int w_counter = 0; w_counter < 8; w_counter++)
  {
      ts_position w_whitePiecePosition = {w_counter,0};
      ts_position w_blackPiecePosition = {w_counter,7};

      // Check main piece position
      _checkPiece(__FUNCTION__, __LINE__, w_whitePiecePosition, w_pieceTab[w_counter], E_WHITE);
      _checkPiece(__FUNCTION__, __LINE__, w_blackPiecePosition, w_pieceTab[w_counter], E_BLACK);

      w_whitePiecePosition = {w_counter,1};
      w_blackPiecePosition = {w_counter,6};

      // Check pawn position
      _checkPiece(__FUNCTION__, __LINE__, w_whitePiecePosition, E_PAWN, E_WHITE);
      _checkPiece(__FUNCTION__, __LINE__, w_blackPiecePosition, E_PAWN, E_BLACK);
  }
}

// Check that the piece only make the movement allowed
void ChessTest::_checkDefaultMovement(const std::string & ai_func,
                                      const unsigned int & ai_line,
                                      const std::string ai_filePath,
                                      const PieceEnum ai_pieceType,
                                      const ColorEnum ai_pieceColor,
                                      const ts_position ai_startPiecePosition,
                                      const std::vector<ts_position> ai_validPiecePosition)
{
  // To know the caller
  std::stringstream w_caller;
  w_caller << "[" << ai_func << ": " << ai_line << "]";

  //Checking default knight movement
  for (int w_cntWidth = 0; w_cntWidth < Constants::C_BOARD_WIDTH; w_cntWidth++)
  {
    for (int w_cntHeight = 0; w_cntHeight < Constants::C_BOARD_HEIGTH; w_cntHeight++)
    {
        ts_position w_testedSquare = {w_cntWidth,w_cntHeight};
        mp_board->processMove( ai_startPiecePosition ,w_testedSquare);

        // If the move is valid for that piece
        if ( TestTools::isInVector<ts_position>(ai_validPiecePosition, w_testedSquare) )
        {
          std::cout << " [TEST] [INFO] Testing valid movement" << std::endl;
          _checkPiece(__FUNCTION__, __LINE__, w_testedSquare, ai_pieceType, ai_pieceColor);
          _checkSquareEmpty(__FUNCTION__, __LINE__, ai_startPiecePosition);

          // reload file
          mp_board->loadGameFile(ai_filePath);
        }
        else
        {
          std::cout << " [TEST] [INFO] Testing not valid movement" << std::endl;
          _checkPiece(__FUNCTION__, __LINE__, ai_startPiecePosition, ai_pieceType, ai_pieceColor);
        }
    }
  }
}

// Check that piece cannot go on already taken square by same-color piece and out of the board squares
void ChessTest::_checkBlockedMovement(const std::string & ai_func,
                                      const unsigned int & ai_line,
                                      const PieceEnum ai_pieceType,
                                      const ColorEnum ai_pieceColor,
                                      const ts_position ai_startPiecePosition,
                                      const std::vector<ts_position> ai_otherPiecePosition)
{
  // To know the caller
  std::stringstream w_caller;
  w_caller << "[" << ai_func << ": " << ai_line << "]";

  //Checking default knight movement
  for (int w_cntWidth = -1; w_cntWidth < Constants::C_BOARD_WIDTH + 1; w_cntWidth++)
  {
    for (int w_cntHeight = -1; w_cntHeight < Constants::C_BOARD_HEIGTH + 1; w_cntHeight++)
    {
      ts_position w_testedSquare = {w_cntWidth,w_cntHeight};
      mp_board->processMove( ai_startPiecePosition ,w_testedSquare);

      // Verifying that main knight doesn't moved
      std::cout << " [TEST] [INFO] Testing piece hasn't moved" << std::endl;
      _checkPiece(__FUNCTION__, __LINE__, ai_startPiecePosition, ai_pieceType, ai_pieceColor);

      // If a piece is on the way we verify that it is still here
      if ( TestTools::isInVector<ts_position>(ai_otherPiecePosition, w_testedSquare) )
      {
        _checkSquareTaken(__FUNCTION__, __LINE__, w_testedSquare);
      }
      else
      {
        _checkSquareEmpty(__FUNCTION__, __LINE__, w_testedSquare);
      }

      // No need to load file again because movement should have been unvalid
    }
  }
}

// Check if the piece is the given type and color
void ChessTest::_checkPiece(const std::string & ai_func, const unsigned int & ai_line, const ts_position ai_piecePosition, const PieceEnum& ai_pieceType, const ColorEnum& ai_pieceColor)
{
  // To know the caller
  std::stringstream w_caller;
  w_caller << "[" << ai_func << ": " << ai_line << "]";

  Piece * wp_piece = mp_board->isPieceOnSquare(ai_piecePosition);

  CPPUNIT_ASSERT_MESSAGE(w_caller.str() + " Piece exist ?", wp_piece != nullptr);
  CPPUNIT_ASSERT_EQUAL_MESSAGE(w_caller.str() + " Right Piece Type ?", wp_piece->getName(), ai_pieceType);
  CPPUNIT_ASSERT_EQUAL_MESSAGE(w_caller.str() + " Right Piece Color ?", wp_piece->getColor(), ai_pieceColor);
}

// Check if the square doesn't have a piece on it
void ChessTest::_checkSquareEmpty(const std::string & ai_func, const unsigned int & ai_line, const ts_position ai_position)
{
  // To know the caller
  std::stringstream w_caller;
  w_caller << "[" << ai_func << ": " << ai_line << "]";

  Piece * wp_piece = mp_board->isPieceOnSquare(ai_position);

  CPPUNIT_ASSERT_MESSAGE(w_caller.str() + " Piece exist ?", wp_piece == nullptr);
}

// Check if the square have a piece on it
void ChessTest::_checkSquareTaken(const std::string & ai_func, const unsigned int & ai_line, const ts_position ai_position)
{
  // To know the caller
  std::stringstream w_caller;
  w_caller << "[" << ai_func << ": " << ai_line << "]";

  Piece * wp_piece = mp_board->isPieceOnSquare(ai_position);

  CPPUNIT_ASSERT_MESSAGE(w_caller.str() + " Piece exist ?", wp_piece != nullptr);
}

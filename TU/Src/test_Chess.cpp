#include "../Include/test_Chess.h"
#include "../Include/test_Tools.h"
#include "../../Include/Piece.h"
#include "../../Include/Constants.h"

const std::string C_KNIGHT_DEFAULT_MOV_FILE_PATH = "./parameters/test_knight_default_movement.txt";
const std::string C_KNIGHT_BLOCKED_MOV_FILE_PATH = "./parameters/test_knight_blocked_movement.txt";
const std::string C_KNIGHT_CAPTURE_FILE_PATH     = "./parameters/test_knight_capture.txt";

const std::string C_BISHOP_DEFAULT_MOV_FILE_PATH = "./parameters/test_bishop_default_movement.txt";
const std::string C_BISHOP_BLOCKED_MOV_FILE_PATH = "./parameters/test_bishop_blocked_movement.txt";
const std::string C_BISHOP_CAPTURE_FILE_PATH     = "./parameters/test_bishop_capture.txt";

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

/**
 *  Test_knight : test the movement of the knight Piece
 *
 *  STEP 1 : Test that the default movement of the knight is correct
 *
 *  STEP 2 : Test that the knight cannot capture a same-color piece or go out of the board
 *
 *  STEP 3 : Test that the knight can capture other color pieces
 **/
void ChessTest::test_knight()
{
  _setup(C_KNIGHT_DEFAULT_MOV_FILE_PATH);

  /*
   *  STEP 1
   */
  const ts_position C_KNIGHT_POS_DEFAULT_MOV = {3,4}; // Knight position on the file C_KNIGHT_DEFAULT_MOV_FILE_PATH
  const std::vector<ts_position> C_VEC_VALID_KNIGHT_MOVE{{4,6},{5,5},{5,3},{4,2},{2,2},{1,3},{1,5},{2,6}}; // All valid move for the knight
  _checkPiece(__FUNCTION__, __LINE__, C_KNIGHT_POS_DEFAULT_MOV, E_KNIGHT, E_WHITE); // Check if file correctly loaded


  //Checking default knight movement
  _checkDefaultMovement(__FUNCTION__, __LINE__, C_KNIGHT_DEFAULT_MOV_FILE_PATH, E_KNIGHT, E_WHITE, C_KNIGHT_POS_DEFAULT_MOV, C_VEC_VALID_KNIGHT_MOVE);


  /*
   *  STEP 2
   */
  const ts_position C_KNIGHT_POS_MAIN  = {2,6};  // Main knight position we want to test on the file C_KNIGHT_BLOCKED_MOV_FILE_PATH
  const ts_position C_KNIGHT_POS_OTHER = {0,5};  // Other knight position on the file C_KNIGHT_BLOCKED_MOV_FILE_PATH
  const ts_position C_PAWN_POS         = {0,7};  // Pawn position on the file C_KNIGHT_BLOCKED_MOV_FILE_PATH
  const ts_position C_KING_POS         = {4,7};  // King position on the file C_KNIGHT_BLOCKED_MOV_FILE_PATH
  const ts_position C_QUEEN_POS        = {4,5};  // Queen position on the file C_KNIGHT_BLOCKED_MOV_FILE_PATH
  const ts_position C_ROOK_POS         = {1,4};  // Rook position on the file C_KNIGHT_BLOCKED_MOV_FILE_PATH
  const ts_position C_BISHOP_POS       = {3,4};  // Bishop position on the file C_KNIGHT_BLOCKED_MOV_FILE_PATH

  // Vector of all pieces position (except main Knight)
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


  /*
   *  STEP 3
   */
  const ts_position C_WHITE_KNIGHT_POS = {3,4};  // Main knight position we want to test on the file C_KNIGHT_CAPTURE_FILE_PATH
  const ts_position C_BLACK_KNIGHT_POS = {4,6};  // Other knight position on the file C_KNIGHT_CAPTURE_FILE_PATH
  const ts_position C_BLACK_PAWN_POS   = {4,2};  // Pawn position on the file C_KNIGHT_CAPTURE_FILE_PATH
  const ts_position C_BLACK_QUEEN_POS  = {5,3};  // Queen position on the file C_KNIGHT_CAPTURE_FILE_PATH
  const ts_position C_BLACK_ROOK_POS   = {2,6};  // Rook position on the file C_KNIGHT_CAPTURE_FILE_PATH
  const ts_position C_BLACK_BISHOP_POS = {5,5};  // Bishop position on the file C_KNIGHT_CAPTURE_FILE_PATH

  // Vector of all piece position (except main Knight)
  const std::vector<ts_position> C_BLACK_PIECE_POSITION {C_BLACK_KNIGHT_POS ,
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

  //Checking default knight movement
  _checkCaptureMovement(__FUNCTION__, __LINE__, C_KNIGHT_CAPTURE_FILE_PATH, E_KNIGHT, E_WHITE, C_WHITE_KNIGHT_POS, C_BLACK_PIECE_POSITION);
}


/**
 *  Test_bishop : test the movement of the bishop Piece
 *
 *  STEP 1 : Test that the default movement of the bishop is correct
 *
 *  STEP 2 : Test that the bishop cannot capture a same-color piece or go out of the board
 *
 *  STEP 3 : Test that the bishop can capture other color pieces
 **/
void ChessTest::test_bishop()
{
  _setup(C_BISHOP_DEFAULT_MOV_FILE_PATH);

  /*
   *  STEP 1
   */
  const ts_position C_BISHOP_POS_DEFAULT_MOV = {3,4}; // Bishop position on the file C_KNIGHT_DEFAULT_MOV_FILE_PATH
  const std::vector<ts_position> C_VEC_VALID_BISHOP_MOVE{{0,7},{1,6},{2,5},{4,3},{5,2},{6,1},{7,0},{6,7},{5,6},{4,5},{2,3},{1,2},{0,1}}; // All valid move for the bishop
  _checkPiece(__FUNCTION__, __LINE__, C_BISHOP_POS_DEFAULT_MOV, E_BISHOP, E_WHITE); // Check if file correctly loaded


  //Checking default bishop movement
  _checkDefaultMovement(__FUNCTION__, __LINE__, C_BISHOP_DEFAULT_MOV_FILE_PATH, E_BISHOP, E_WHITE, C_BISHOP_POS_DEFAULT_MOV, C_VEC_VALID_BISHOP_MOVE);


  /*
   *  STEP 2
   */
  const ts_position C_BISHOP_POS_MAIN_1 = {3,3};  // First Main bishop position we want to test on the file C_BISHOP_BLOCKED_MOV_FILE_PATH
  const ts_position C_QUEEN_POS         = {7,7};  // Queen position on the file C_BISHOP_BLOCKED_MOV_FILE_PATH
  const ts_position C_PAWN_POS          = {2,4};  // Pawn position on the file C_BISHOP_BLOCKED_MOV_FILE_PATH
  const ts_position C_KNIGHT_POS        = {5,1};  // Knight position on the file C_BISHOP_BLOCKED_MOV_FILE_PATH
  const ts_position C_BISHOP_POS_OTHER  = {0,0};  // Other bishop position on the file C_BISHOP_BLOCKED_MOV_FILE_PATH

  const ts_position C_BISHOP_POS_MAIN_2 = {2,7};  // Second Main bishop position we want to test on the file C_BISHOP_BLOCKED_MOV_FILE_PATH
  const ts_position C_ROOK_POS          = {3,6};  // Rook position on the file C_BISHOP_BLOCKED_MOV_FILE_PATH
  const ts_position C_KING_POS          = {0,5};  // King position on the file C_BISHOP_BLOCKED_MOV_FILE_PATH

  // Vector of all blocked position (except main_1 Bishop) for first test 1
  const std::vector<ts_position> C_BLOCKED_SQUARES_1 {C_BISHOP_POS_MAIN_1,
                                                    C_QUEEN_POS ,
                                                    C_PAWN_POS,
                                                    C_KNIGHT_POS,
                                                    C_BISHOP_POS_OTHER,
                                                    {0,6}, // Square blocked by pawn
                                                    {1,5}, // Square blocked by pawn
                                                    {6,0}}; // Square blocked by knight

  // Vector of all blocked position (except main_2 Bishop) for first test 2
  const std::vector<ts_position> C_BLOCKED_SQUARES_2 {C_BISHOP_POS_MAIN_2,
                                                      C_ROOK_POS ,
                                                      C_KING_POS,
                                                      {4,5}, // Square blocked by rook
                                                      {5,4}, // Square blocked by rook
                                                      {6,3}, // Square blocked by rook
                                                      {7,2}}; // Square blocked by rook

  // Loading test file
  mp_board->loadGameFile(C_BISHOP_BLOCKED_MOV_FILE_PATH);

  // Check if file correctly loaded
  _checkPiece(__FUNCTION__, __LINE__, C_BISHOP_POS_MAIN_1, E_BISHOP, E_BLACK);
  _checkPiece(__FUNCTION__, __LINE__, C_BISHOP_POS_MAIN_2, E_BISHOP, E_BLACK);
  _checkPiece(__FUNCTION__, __LINE__, C_QUEEN_POS, E_QUEEN, E_BLACK);
  _checkPiece(__FUNCTION__, __LINE__, C_PAWN_POS, E_PAWN, E_BLACK);
  _checkPiece(__FUNCTION__, __LINE__, C_KNIGHT_POS, E_KNIGHT, E_BLACK);
  _checkPiece(__FUNCTION__, __LINE__, C_BISHOP_POS_OTHER, E_BISHOP, E_BLACK);
  _checkPiece(__FUNCTION__, __LINE__, C_ROOK_POS, E_ROOK, E_BLACK);
  _checkPiece(__FUNCTION__, __LINE__, C_KING_POS, E_KING, E_BLACK);

  //Checking default knight movement
  _checkBlockedMovement(__FUNCTION__, __LINE__, E_BISHOP, E_BLACK, C_BISHOP_POS_MAIN_1, C_BLOCKED_SQUARES_1);
  _checkBlockedMovement(__FUNCTION__, __LINE__, E_BISHOP, E_BLACK, C_BISHOP_POS_MAIN_2, C_BLOCKED_SQUARES_2);


  /*
   *  STEP 3
   */
  const ts_position C_WHITE_BISHOP_POS_1 = {3,4};  // First bishop position we want to test on the file C_BISHOP_CAPTURE_FILE_PATH
  const ts_position C_BLACK_BISHOP_POS   = {5,6};  // Other bishop position on the file C_BISHOP_CAPTURE_FILE_PATH
  const ts_position C_BLACK_ROOK_POS     = {2,5};  // Rook position on the file C_BISHOP_CAPTURE_FILE_PATH
  const ts_position C_BLACK_QUEEN_POS    = {0,1};  // Queen position on the file C_BISHOP_CAPTURE_FILE_PATH
  const ts_position C_BLACK_KNIGHT_POS   = {7,0};  // Knight position on the file C_BISHOP_CAPTURE_FILE_PATH

  const ts_position C_WHITE_BISHOP_POS_2 = {4,0};  // Second bishop position we want to test on the file C_BISHOP_CAPTURE_FILE_PATH
  const ts_position C_BLACK_KNIGHT_POS_2 = {2,2};  // Knight position on the file C_BISHOP_CAPTURE_FILE_PATH
  const ts_position C_BLACK_PAWN_POS     = {5,1};  // Knight position on the file C_BISHOP_CAPTURE_FILE_PATH

  // Vector of all piece position (except main Bishop) for test 1
  const std::vector<ts_position> C_BLACK_PIECE_POSITION_1 {C_BLACK_BISHOP_POS ,
                                                          C_BLACK_ROOK_POS,
                                                          C_BLACK_QUEEN_POS,
                                                          C_BLACK_KNIGHT_POS};

  // Vector of all piece position (except main Bishop) for test 2
  const std::vector<ts_position> C_BLACK_PIECE_POSITION_2 {C_BLACK_KNIGHT_POS_2 ,
                                                          C_BLACK_PAWN_POS};

  // Loading test file
  mp_board->loadGameFile(C_BISHOP_CAPTURE_FILE_PATH);

  // Check if file correctly loaded
  _checkPiece(__FUNCTION__, __LINE__, C_WHITE_BISHOP_POS_1, E_BISHOP, E_WHITE);
  _checkPiece(__FUNCTION__, __LINE__, C_WHITE_BISHOP_POS_2, E_BISHOP, E_WHITE);
  _checkPiece(__FUNCTION__, __LINE__, C_BLACK_BISHOP_POS, E_BISHOP, E_BLACK);
  _checkPiece(__FUNCTION__, __LINE__, C_BLACK_ROOK_POS, E_ROOK, E_BLACK);
  _checkPiece(__FUNCTION__, __LINE__, C_BLACK_QUEEN_POS, E_QUEEN, E_BLACK);
  _checkPiece(__FUNCTION__, __LINE__, C_BLACK_KNIGHT_POS, E_KNIGHT, E_BLACK);
  _checkPiece(__FUNCTION__, __LINE__, C_BLACK_KNIGHT_POS_2, E_KNIGHT, E_BLACK);
  _checkPiece(__FUNCTION__, __LINE__, C_BLACK_PAWN_POS, E_PAWN, E_BLACK);

  //Checking default bishop movement
  _checkCaptureMovement(__FUNCTION__, __LINE__, C_BISHOP_CAPTURE_FILE_PATH, E_BISHOP, E_WHITE, C_WHITE_BISHOP_POS_1, C_BLACK_PIECE_POSITION_1);
  _checkCaptureMovement(__FUNCTION__, __LINE__, C_BISHOP_CAPTURE_FILE_PATH, E_BISHOP, E_WHITE, C_WHITE_BISHOP_POS_2, C_BLACK_PIECE_POSITION_2);

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
  std::cout << " [TEST] [INFO] Testing default movement : " << w_caller.str() << std::endl;

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
                                      const std::vector<ts_position> ai_blockedSquares)
{
  // To know the caller
  std::stringstream w_caller;
  w_caller << "[" << ai_func << ": " << ai_line << "]";
  std::cout << " [TEST] [INFO] Testing blocked movement : " << w_caller.str()  << std::endl;

  //Checking default piece movement
  for (int w_cntWidth = -1; w_cntWidth < Constants::C_BOARD_WIDTH + 1; w_cntWidth++)
  {
    for (int w_cntHeight = -1; w_cntHeight < Constants::C_BOARD_HEIGTH + 1; w_cntHeight++)
    {
      ts_position w_testedSquare = {w_cntWidth,w_cntHeight};

      // If the square is a blocked one or if the square is out of board
      if ( TestTools::isInVector<ts_position>(ai_blockedSquares, w_testedSquare)  || (w_cntWidth < 0) || (w_cntHeight < 0))
      {
        mp_board->processMove( ai_startPiecePosition ,w_testedSquare);

        // Verifying that main piece doesn't moved
        std::cout << " [TEST] [INFO] Testing piece hasn't moved" << std::endl;
        _checkPiece(__FUNCTION__, __LINE__, ai_startPiecePosition, ai_pieceType, ai_pieceColor);
      }

      // No need to load file again because movement should have been unvalid
    }
  }
}

// Check that piece can capture the other pieces
void ChessTest::_checkCaptureMovement(const std::string & ai_func,
                                      const unsigned int & ai_line,
                                      const std::string ai_filePath,
                                      const PieceEnum ai_pieceType,
                                      const ColorEnum ai_pieceColor,
                                      const ts_position ai_startPiecePosition,
                                      const std::vector<ts_position> ai_otherPiecePosition)
{
  // To know the caller
  std::stringstream w_caller;
  w_caller << "[" << ai_func << ": " << ai_line << "]";
  std::cout << " [TEST] [INFO] Testing capture movement : " << w_caller.str() << std::endl;

  std::vector<ts_position>::const_iterator w_pieceIt = ai_otherPiecePosition.begin();

  for (; w_pieceIt != ai_otherPiecePosition.end(); w_pieceIt++)
  {
      mp_board->processMove( ai_startPiecePosition , *w_pieceIt);

      _checkPiece(__FUNCTION__, __LINE__, *w_pieceIt, ai_pieceType, ai_pieceColor);
      _checkSquareEmpty(__FUNCTION__, __LINE__, ai_startPiecePosition);

      mp_board->loadGameFile(ai_filePath);
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

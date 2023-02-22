#include "../Include/test_Bishop.h"
#include "../Include/test_Tools.h"
#include "../../Include/Piece.h"
#include "../../Include/Constants.h"
#include "../../Include/Logger.h"

const std::string C_BISHOP_DEFAULT_MOV_FILE_PATH = "./parameters/test_bishop_default_movement.txt";
const std::string C_BISHOP_BLOCKED_MOV_FILE_PATH = "./parameters/test_bishop_blocked_movement.txt";
const std::string C_BISHOP_CAPTURE_FILE_PATH     = "./parameters/test_bishop_capture.txt";

CPPUNIT_TEST_SUITE_REGISTRATION(BishopTest);

BishopTest::BishopTest()
{}

void BishopTest::setUp()
{}

void BishopTest::_setup(std::string w_filePath)
{
  mp_board = new Board(w_filePath);
}

void BishopTest::tearDown()
{
  if (mp_board != nullptr)
  {
    delete mp_board;
  }
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
void BishopTest::test_bishop()
{
  _setup(C_BISHOP_DEFAULT_MOV_FILE_PATH);

  /*
   *  STEP 1
   */
  const ts_position C_BISHOP_POS_DEFAULT_MOV = {3,4}; // Bishop position on the file C_KNIGHT_DEFAULT_MOV_FILE_PATH
  const std::vector<ts_position> C_VEC_VALID_BISHOP_MOVE{{0,7},{1,6},{2,5},{4,3},{5,2},{6,1},{7,0},{6,7},{5,6},{4,5},{2,3},{1,2},{0,1}}; // All valid move for the bishop
  TestTools::_checkPiece(__FUNCTION__, __LINE__, mp_board, C_BISHOP_POS_DEFAULT_MOV, E_BISHOP, E_WHITE); // Check if file correctly loaded


  //Checking default bishop movement
  TestTools::_checkDefaultMovement(__FUNCTION__, __LINE__, mp_board, C_BISHOP_DEFAULT_MOV_FILE_PATH, E_BISHOP, E_WHITE, C_BISHOP_POS_DEFAULT_MOV, C_VEC_VALID_BISHOP_MOVE);


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
  TestTools::_checkPiece(__FUNCTION__, __LINE__, mp_board, C_BISHOP_POS_MAIN_1, E_BISHOP, E_BLACK);
  TestTools::_checkPiece(__FUNCTION__, __LINE__, mp_board, C_BISHOP_POS_MAIN_2, E_BISHOP, E_BLACK);
  TestTools::_checkPiece(__FUNCTION__, __LINE__, mp_board, C_QUEEN_POS, E_QUEEN, E_BLACK);
  TestTools::_checkPiece(__FUNCTION__, __LINE__, mp_board, C_PAWN_POS, E_PAWN, E_BLACK);
  TestTools::_checkPiece(__FUNCTION__, __LINE__, mp_board, C_KNIGHT_POS, E_KNIGHT, E_BLACK);
  TestTools::_checkPiece(__FUNCTION__, __LINE__, mp_board, C_BISHOP_POS_OTHER, E_BISHOP, E_BLACK);
  TestTools::_checkPiece(__FUNCTION__, __LINE__, mp_board, C_ROOK_POS, E_ROOK, E_BLACK);
  TestTools::_checkPiece(__FUNCTION__, __LINE__, mp_board, C_KING_POS, E_KING, E_BLACK);

  //Checking default knight movement
  TestTools::_checkBlockedMovement(__FUNCTION__, __LINE__, mp_board, E_BISHOP, E_BLACK, C_BISHOP_POS_MAIN_1, C_BLOCKED_SQUARES_1);
  TestTools::_checkBlockedMovement(__FUNCTION__, __LINE__, mp_board, E_BISHOP, E_BLACK, C_BISHOP_POS_MAIN_2, C_BLOCKED_SQUARES_2);


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
  TestTools::_checkPiece(__FUNCTION__, __LINE__, mp_board, C_WHITE_BISHOP_POS_1, E_BISHOP, E_WHITE);
  TestTools::_checkPiece(__FUNCTION__, __LINE__, mp_board, C_WHITE_BISHOP_POS_2, E_BISHOP, E_WHITE);
  TestTools::_checkPiece(__FUNCTION__, __LINE__, mp_board, C_BLACK_BISHOP_POS, E_BISHOP, E_BLACK);
  TestTools::_checkPiece(__FUNCTION__, __LINE__, mp_board, C_BLACK_ROOK_POS, E_ROOK, E_BLACK);
  TestTools::_checkPiece(__FUNCTION__, __LINE__, mp_board, C_BLACK_QUEEN_POS, E_QUEEN, E_BLACK);
  TestTools::_checkPiece(__FUNCTION__, __LINE__, mp_board, C_BLACK_KNIGHT_POS, E_KNIGHT, E_BLACK);
  TestTools::_checkPiece(__FUNCTION__, __LINE__, mp_board, C_BLACK_KNIGHT_POS_2, E_KNIGHT, E_BLACK);
  TestTools::_checkPiece(__FUNCTION__, __LINE__, mp_board, C_BLACK_PAWN_POS, E_PAWN, E_BLACK);

  //Checking default bishop movement
  TestTools::_checkCaptureMovement(__FUNCTION__, __LINE__, mp_board, C_BISHOP_CAPTURE_FILE_PATH, E_BISHOP, E_WHITE, C_WHITE_BISHOP_POS_1, C_BLACK_PIECE_POSITION_1);
  TestTools::_checkCaptureMovement(__FUNCTION__, __LINE__, mp_board, C_BISHOP_CAPTURE_FILE_PATH, E_BISHOP, E_WHITE, C_WHITE_BISHOP_POS_2, C_BLACK_PIECE_POSITION_2);

}

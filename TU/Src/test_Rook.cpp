#include "../Include/test_Rook.h"
#include "../Include/test_Tools.h"
#include "../../Include/Piece.h"
#include "../../Include/Constants.h"
#include "../../Include/Logger.h"

const std::string C_ROOK_DEFAULT_MOV_FILE_PATH = "./parameters/rook_param/test_rook_default_movement.txt";
const std::string C_ROOK_BLOCKED_MOV_FILE_PATH = "./parameters/rook_param/test_rook_blocked_movement.txt";
const std::string C_ROOK_CAPTURE_FILE_PATH     = "./parameters/rook_param/test_rook_capture.txt";

CPPUNIT_TEST_SUITE_REGISTRATION(RookTest);

RookTest::RookTest()
{}

void RookTest::setUp()
{}

void RookTest::_setup(std::string w_filePath)
{
  mp_board = new Board(w_filePath);
}

void RookTest::tearDown()
{
  if (mp_board != nullptr)
  {
    delete mp_board;
  }
}

/**
 *  Test_rook : test the movement of the rook Piece
 *
 *  STEP 1 : Test that the default movement of the rook is correct
 *
 *  STEP 2 : Test that the rook cannot capture a same-color piece or go out of the board
 *
 *  STEP 3 : Test that the rook can capture other color pieces
 **/
void RookTest::test_rook()
{
  _setup(C_ROOK_DEFAULT_MOV_FILE_PATH);

  /*
   *  STEP 1
   */
  const ts_position C_ROOK_POS_DEFAULT_MOV = {3,4}; // Rook position on the file C_KNIGHT_DEFAULT_MOV_FILE_PATH
  const std::vector<ts_position> C_VEC_VALID_ROOK_MOVE{{3,7},{3,6},{3,5},{3,3},{3,2},{3,1},{3,0},{0,4},{1,4},{2,4},{4,4},{5,4},{6,4},{7,4}}; // All valid move for the rook
  TestTools::_checkPiece(__FUNCTION__, __LINE__, mp_board, C_ROOK_POS_DEFAULT_MOV, E_ROOK, E_WHITE); // Check if file correctly loaded


  //Checking default rook movement
  TestTools::_checkDefaultMovement(__FUNCTION__, __LINE__, mp_board, C_ROOK_DEFAULT_MOV_FILE_PATH, E_ROOK, E_WHITE, C_ROOK_POS_DEFAULT_MOV, C_VEC_VALID_ROOK_MOVE);


  /*
   *  STEP 2
   */
  const ts_position C_ROOK_POS_MAIN_1 = {4,3};  // First Main rook position we want to test on the file C_ROOK_BLOCKED_MOV_FILE_PATH
  const ts_position C_QUEEN_POS         = {6,3};  // Queen position on the file C_ROOK_BLOCKED_MOV_FILE_PATH
  const ts_position C_PAWN_POS          = {3,3};  // Pawn position on the file C_ROOK_BLOCKED_MOV_FILE_PATH
  const ts_position C_KING_POS        = {4,7};  // King position on the file C_ROOK_BLOCKED_MOV_FILE_PATH
  const ts_position C_BISHOP_POS  = {4,0};  // Bishop position on the file C_ROOK_BLOCKED_MOV_FILE_PATH

  const ts_position C_ROOK_POS_MAIN_2 = {1,1};  // Second Main rook position we want to test on the file C_ROOK_BLOCKED_MOV_FILE_PATH
  const ts_position C_ROOK_POS          = {1,6};  // Rook position on the file C_ROOK_BLOCKED_MOV_FILE_PATH
  const ts_position C_KNIGHT_POS          = {3,1};  // Knight position on the file C_ROOK_BLOCKED_MOV_FILE_PATH

  // Vector of all blocked position (except main_1 Rook) for first test 1
  const std::vector<ts_position> C_BLOCKED_SQUARES_1 {C_ROOK_POS_MAIN_1,
                                                    C_QUEEN_POS ,
                                                    C_PAWN_POS,
                                                    C_KING_POS,
                                                    C_BISHOP_POS,
                                                    {7,3}, // Square blocked by queen
                                                    {0,3}, // Square blocked by pawn
                                                    {1,3},  // Square blocked by pawn
                                                    {2,3}}; // Square blocked by pawn

  // Vector of all blocked position (except main_2 Rook) for first test 2
  const std::vector<ts_position> C_BLOCKED_SQUARES_2 {C_ROOK_POS_MAIN_2,
                                                      C_ROOK_POS ,
                                                      C_KNIGHT_POS,
                                                      {1,7}, // Square blocked by rook
                                                      {4,1}, // Square blocked by knight
                                                      {5,1}, // Square blocked by knight
                                                      {6,1}, // Square blocked by knight
                                                      {7,1}}; // Square blocked by knight

  // Loading test file
  mp_board->loadGameFile(C_ROOK_BLOCKED_MOV_FILE_PATH);

  // Check if file correctly loaded
  TestTools::_checkPiece(__FUNCTION__, __LINE__, mp_board, C_ROOK_POS_MAIN_1, E_ROOK, E_BLACK);
  TestTools::_checkPiece(__FUNCTION__, __LINE__, mp_board, C_ROOK_POS_MAIN_2, E_ROOK, E_BLACK);
  TestTools::_checkPiece(__FUNCTION__, __LINE__, mp_board, C_QUEEN_POS, E_QUEEN, E_BLACK);
  TestTools::_checkPiece(__FUNCTION__, __LINE__, mp_board, C_PAWN_POS, E_PAWN, E_BLACK);
  TestTools::_checkPiece(__FUNCTION__, __LINE__, mp_board, C_KNIGHT_POS, E_KNIGHT, E_BLACK);
  TestTools::_checkPiece(__FUNCTION__, __LINE__, mp_board, C_BISHOP_POS, E_BISHOP, E_BLACK);
  TestTools::_checkPiece(__FUNCTION__, __LINE__, mp_board, C_ROOK_POS, E_ROOK, E_BLACK);
  TestTools::_checkPiece(__FUNCTION__, __LINE__, mp_board, C_KING_POS, E_KING, E_BLACK);

  //Checking default knight movement
  TestTools::_checkBlockedMovement(__FUNCTION__, __LINE__, mp_board, E_ROOK, E_BLACK, C_ROOK_POS_MAIN_1, C_BLOCKED_SQUARES_1);
  TestTools::_checkBlockedMovement(__FUNCTION__, __LINE__, mp_board, E_ROOK, E_BLACK, C_ROOK_POS_MAIN_2, C_BLOCKED_SQUARES_2);


  /*
   *  STEP 3
   */
  // const ts_position C_WHITE_ROOK_POS_1 = {3,4};  // First rook position we want to test on the file C_ROOK_CAPTURE_FILE_PATH
  // const ts_position C_BLACK_ROOK_POS   = {5,6};  // Other rook position on the file C_ROOK_CAPTURE_FILE_PATH
  // const ts_position C_BLACK_ROOK_POS     = {2,5};  // Rook position on the file C_ROOK_CAPTURE_FILE_PATH
  // const ts_position C_BLACK_QUEEN_POS    = {0,1};  // Queen position on the file C_ROOK_CAPTURE_FILE_PATH
  // const ts_position C_BLACK_KNIGHT_POS   = {7,0};  // Knight position on the file C_ROOK_CAPTURE_FILE_PATH
  //
  // const ts_position C_WHITE_ROOK_POS_2 = {4,0};  // Second rook position we want to test on the file C_ROOK_CAPTURE_FILE_PATH
  // const ts_position C_BLACK_KNIGHT_POS_2 = {2,2};  // Knight position on the file C_ROOK_CAPTURE_FILE_PATH
  // const ts_position C_BLACK_PAWN_POS     = {5,1};  // Knight position on the file C_ROOK_CAPTURE_FILE_PATH
  //
  // // Vector of all piece position (except main Rook) for test 1
  // const std::vector<ts_position> C_BLACK_PIECE_POSITION_1 {C_BLACK_ROOK_POS ,
  //                                                         C_BLACK_ROOK_POS,
  //                                                         C_BLACK_QUEEN_POS,
  //                                                         C_BLACK_KNIGHT_POS};
  //
  // // Vector of all piece position (except main Rook) for test 2
  // const std::vector<ts_position> C_BLACK_PIECE_POSITION_2 {C_BLACK_KNIGHT_POS_2 ,
  //                                                         C_BLACK_PAWN_POS};
  //
  // // Loading test file
  // mp_board->loadGameFile(C_ROOK_CAPTURE_FILE_PATH);
  //
  // // Check if file correctly loaded
  // TestTools::_checkPiece(__FUNCTION__, __LINE__, mp_board, C_WHITE_ROOK_POS_1, E_ROOK, E_WHITE);
  // TestTools::_checkPiece(__FUNCTION__, __LINE__, mp_board, C_WHITE_ROOK_POS_2, E_ROOK, E_WHITE);
  // TestTools::_checkPiece(__FUNCTION__, __LINE__, mp_board, C_BLACK_ROOK_POS, E_ROOK, E_BLACK);
  // TestTools::_checkPiece(__FUNCTION__, __LINE__, mp_board, C_BLACK_ROOK_POS, E_ROOK, E_BLACK);
  // TestTools::_checkPiece(__FUNCTION__, __LINE__, mp_board, C_BLACK_QUEEN_POS, E_QUEEN, E_BLACK);
  // TestTools::_checkPiece(__FUNCTION__, __LINE__, mp_board, C_BLACK_KNIGHT_POS, E_KNIGHT, E_BLACK);
  // TestTools::_checkPiece(__FUNCTION__, __LINE__, mp_board, C_BLACK_KNIGHT_POS_2, E_KNIGHT, E_BLACK);
  // TestTools::_checkPiece(__FUNCTION__, __LINE__, mp_board, C_BLACK_PAWN_POS, E_PAWN, E_BLACK);
  //
  // //Checking default rook movement
  // TestTools::_checkCaptureMovement(__FUNCTION__, __LINE__, mp_board, C_ROOK_CAPTURE_FILE_PATH, E_ROOK, E_WHITE, C_WHITE_ROOK_POS_1, C_BLACK_PIECE_POSITION_1);
  // TestTools::_checkCaptureMovement(__FUNCTION__, __LINE__, mp_board, C_ROOK_CAPTURE_FILE_PATH, E_ROOK, E_WHITE, C_WHITE_ROOK_POS_2, C_BLACK_PIECE_POSITION_2);

}

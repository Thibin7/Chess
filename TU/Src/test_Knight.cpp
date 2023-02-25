#include "../Include/test_Knight.h"
#include "../Include/test_Tools.h"
#include "../../Include/Piece.h"
#include "../../Include/Constants.h"
#include "../../Include/Logger.h"

const std::string C_KNIGHT_DEFAULT_MOV_FILE_PATH = "./parameters/knight_param/test_knight_default_movement.txt";
const std::string C_KNIGHT_BLOCKED_MOV_FILE_PATH = "./parameters/knight_param/test_knight_blocked_movement.txt";
const std::string C_KNIGHT_CAPTURE_FILE_PATH     = "./parameters/knight_param/test_knight_capture.txt";

CPPUNIT_TEST_SUITE_REGISTRATION(KnightTest);

KnightTest::KnightTest()
{}

void KnightTest::setUp()
{}

void KnightTest::_setup(std::string w_filePath)
{
  mp_board = new Board(w_filePath);
}

void KnightTest::tearDown()
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
void KnightTest::test_knight()
{
  _setup(C_KNIGHT_DEFAULT_MOV_FILE_PATH);

  /*
   *  STEP 1
   */
  const ts_position C_KNIGHT_POS_DEFAULT_MOV = {3,4}; // Knight position on the file C_KNIGHT_DEFAULT_MOV_FILE_PATH
  const std::vector<ts_position> C_VEC_VALID_KNIGHT_MOVE{{4,6},{5,5},{5,3},{4,2},{2,2},{1,3},{1,5},{2,6}}; // All valid move for the knight
  TestTools::_checkPiece(__FUNCTION__, __LINE__, mp_board, C_KNIGHT_POS_DEFAULT_MOV, E_KNIGHT, E_WHITE); // Check if file correctly loaded


  //Checking default knight movement
  TestTools::_checkDefaultMovement(__FUNCTION__, __LINE__, mp_board, C_KNIGHT_DEFAULT_MOV_FILE_PATH, E_KNIGHT, E_WHITE, C_KNIGHT_POS_DEFAULT_MOV, C_VEC_VALID_KNIGHT_MOVE);


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
  TestTools::_checkPiece(__FUNCTION__, __LINE__, mp_board, C_KNIGHT_POS_MAIN, E_KNIGHT, E_BLACK);
  TestTools::_checkPiece(__FUNCTION__, __LINE__, mp_board, C_KNIGHT_POS_OTHER, E_KNIGHT, E_BLACK);
  TestTools::_checkPiece(__FUNCTION__, __LINE__, mp_board, C_PAWN_POS, E_PAWN, E_BLACK);
  TestTools::_checkPiece(__FUNCTION__, __LINE__, mp_board, C_KING_POS, E_KING, E_BLACK);
  TestTools::_checkPiece(__FUNCTION__, __LINE__, mp_board, C_QUEEN_POS, E_QUEEN, E_BLACK);
  TestTools::_checkPiece(__FUNCTION__, __LINE__, mp_board, C_ROOK_POS, E_ROOK, E_BLACK);
  TestTools::_checkPiece(__FUNCTION__, __LINE__, mp_board, C_BISHOP_POS, E_BISHOP, E_BLACK);

  //Checking default knight movement
  TestTools::_checkBlockedMovement(__FUNCTION__, __LINE__, mp_board, E_KNIGHT, E_BLACK, C_KNIGHT_POS_MAIN, C_OTHER_PIECE_POSITION);


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
  TestTools::_checkPiece(__FUNCTION__, __LINE__, mp_board, C_WHITE_KNIGHT_POS, E_KNIGHT, E_WHITE);
  TestTools::_checkPiece(__FUNCTION__, __LINE__, mp_board, C_BLACK_KNIGHT_POS, E_KNIGHT, E_BLACK);
  TestTools::_checkPiece(__FUNCTION__, __LINE__, mp_board, C_BLACK_PAWN_POS, E_PAWN, E_BLACK);
  TestTools::_checkPiece(__FUNCTION__, __LINE__, mp_board, C_BLACK_QUEEN_POS, E_QUEEN, E_BLACK);
  TestTools::_checkPiece(__FUNCTION__, __LINE__, mp_board, C_BLACK_ROOK_POS, E_ROOK, E_BLACK);
  TestTools::_checkPiece(__FUNCTION__, __LINE__, mp_board, C_BLACK_BISHOP_POS, E_BISHOP, E_BLACK);

  //Checking default knight movement
  TestTools::_checkCaptureMovement(__FUNCTION__, __LINE__, mp_board, C_KNIGHT_CAPTURE_FILE_PATH, E_KNIGHT, E_WHITE, C_WHITE_KNIGHT_POS, C_BLACK_PIECE_POSITION);
}

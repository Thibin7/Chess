#ifndef TESTCHESS_H
#define TESTCHESS_H

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/Portability.h>
#include "../../Include/Board.h"

class ChessTest : public CppUnit::TestFixture
{
  public:
    CPPUNIT_TEST_SUITE(ChessTest);
    CPPUNIT_TEST(test_knight);
    CPPUNIT_TEST(test_bishop);
    //CPPUNIT_TEST(test_rook);
    //CPPUNIT_TEST(test_king);
    CPPUNIT_TEST_SUITE_END();

  public:
    ChessTest();

    void setUp();
    void tearDown();

    void test_knight();
    void test_bishop();
    void test_rook();
    void test_king();

  private:
    Board * mp_board {nullptr};

    void _setup(std::string w_filePath);

    void _checkDefaultBoard(const std::string & ai_func, const unsigned int & ai_line);
    void _checkPiece(const std::string & ai_func, const unsigned int & ai_line, const ts_position ai_piecePosition, const PieceEnum& ai_pieceType, const ColorEnum& ai_pieceColor);
    void _checkSquareEmpty(const std::string & ai_func, const unsigned int & ai_line, const ts_position ai_position);
    void _checkSquareTaken(const std::string & ai_func, const unsigned int & ai_line, const ts_position ai_position);

    void _checkDefaultMovement(const std::string & ai_func,
                              const unsigned int & ai_line,
                              const std::string ai_filePath,
                              const PieceEnum ai_pieceType,
                              const ColorEnum ai_pieceColor,
                              const ts_position ai_startPiecePosition,
                              const std::vector<ts_position> ai_validPiecePosition);

    void _checkBlockedMovement(const std::string & ai_func,
                              const unsigned int & ai_line,
                              const PieceEnum ai_pieceType,
                              const ColorEnum ai_pieceColor,
                              const ts_position ai_startPiecePosition,
                              const std::vector<ts_position> ai_otherPiecePosition);

    void _checkCaptureMovement(const std::string & ai_func,
                              const unsigned int & ai_line,
                              const std::string ai_filePath,
                              const PieceEnum ai_pieceType,
                              const ColorEnum ai_pieceColor,
                              const ts_position ai_startPiecePosition,
                              const std::vector<ts_position> ai_otherPiecePosition);
};

#endif

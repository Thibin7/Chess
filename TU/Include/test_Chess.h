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
    CPPUNIT_TEST_SUITE_END();

  public:
    ChessTest();

    void setUp();
    void tearDown();

    void test_knight();
    void test_bishop();

  private:
    Board * mp_board {nullptr};

    void _checkDefaultBoard(const std::string & ai_func, const unsigned int & ai_line);
    void _checkPiece(const std::string & ai_func, const unsigned int & ai_line, Piece * ai_piece, const PieceEnum& ai_pieceType, const ColorEnum& ai_pieceColor);

};

#endif

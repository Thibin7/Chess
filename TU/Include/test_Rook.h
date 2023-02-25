#ifndef TESTROOK_H
#define TESTROOK_H

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/Portability.h>
#include "../../Include/Board.h"

class RookTest : public CppUnit::TestFixture
{
  public:
    CPPUNIT_TEST_SUITE(RookTest);
    CPPUNIT_TEST(test_rook);
    CPPUNIT_TEST_SUITE_END();

  public:
    RookTest();

    void setUp();
    void tearDown();

    void test_rook();

  private:
    Board * mp_board {nullptr};

    void _setup(std::string w_filePath);
};

#endif

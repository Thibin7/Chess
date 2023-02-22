#ifndef TESTKNIGHT_H
#define TESTKNIGHT_H

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/Portability.h>
#include "../../Include/Board.h"

class KnightTest : public CppUnit::TestFixture
{
  public:
    CPPUNIT_TEST_SUITE(KnightTest);
    CPPUNIT_TEST(test_knight);
    CPPUNIT_TEST_SUITE_END();

  public:
    KnightTest();

    void setUp();
    void tearDown();

    void test_knight();

  private:
    Board * mp_board {nullptr};

    void _setup(std::string w_filePath);
};

#endif

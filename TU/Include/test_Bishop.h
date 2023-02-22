#ifndef TESTBISHOP_H
#define TESTBISHOP_H

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/Portability.h>
#include "../../Include/Board.h"

class BishopTest : public CppUnit::TestFixture
{
  public:
    CPPUNIT_TEST_SUITE(BishopTest);
    CPPUNIT_TEST(test_bishop);
    CPPUNIT_TEST_SUITE_END();

  public:
    BishopTest();

    void setUp();
    void tearDown();

    void test_bishop();

  private:
    Board * mp_board {nullptr};

    void _setup(std::string w_filePath);
};

#endif

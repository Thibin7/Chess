#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/XmlOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TestRunner.h>
#include <cppunit/tools/XmlElement.h>
#include <cppunit/Test.h>


int main(int argc, char * argv[])
{
  //Create the event manager and test controller
  CppUnit::TestResult w_controller;

  std::string w_test = "";
  if ( argc == 2 )
  {
      w_test = argv[1];
  }

  // Add a listener that collects test result
  CppUnit::TestResultCollector w_result;
  w_controller.addListener(&w_result);

  // Add a listener that print dots as test run
  CppUnit::BriefTestProgressListener w_progress;
  w_controller.addListener(&w_progress);

  // Add the top suite to the test runner
  CppUnit::TestRunner w_runner;
  CppUnit::Test * w_tests = CppUnit::TestFactoryRegistry::getRegistry().makeTest();
  w_runner.addTest(w_tests);

  if ( w_test == "" )
  {
    std::cout << "Launch all tests" << std::endl;
    w_runner.run(w_controller);
  }
  else
  {
     try
     {
       std::cout << "Launch test : " << w_test << std::endl;
       w_runner.run(w_controller, w_test);
     }
     catch (std::exception &e)
     {
       std::cout << "Eception caught { " << e.what() << " }" << std::endl;
     }
  }

  // Print test result in terminal
  CppUnit::CompilerOutputter w_outputter(&w_result, CppUnit::stdCOut());
  w_outputter.write();

  // Print test global results in xml file
  CppUnit::OFileStream w_file("Result_CppUnit.xml");
  CppUnit::XmlOutputter XmlOutputter(&w_result, w_file, "UTF-8");
  XmlOutputter.write();

  return w_result.wasSuccessful() ? 0 : 1;
}

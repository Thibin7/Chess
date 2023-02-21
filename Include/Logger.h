#ifndef LOGGER_H
#define LOGGER_H

#include <stdio.h>
#include <iostream>

const std::string LOG_SOFT = " [SOFT]";
const std::string LOG_GAME = " [GAME]";
const std::string LOG_TEST = " [TEST]";

namespace TraceLog
{

// Class Logger
class Logger
{
  public:
    Logger();
    ~Logger();


    // Warning logger
    // 1 definition for logger with argument and one without
    template<typename... Args>
    void warning(std::string ai_scope, std::string ai_msg, Args... args)
    {
      std::string w_str = ai_scope + " [WARNING] " + ai_msg;

      char w_buffer2[100];
      sprintf(w_buffer2, w_str.c_str(), args...);

      std::cout <<  "\033[33m" << w_buffer2 <<  "\033[0m" << std::endl;
    }

    void warning(std::string ai_scope, std::string ai_msg)
    {
      std::string w_str = ai_scope + " [WARNING] " + ai_msg;
      std::cout <<  "\033[33m" << w_str <<  "\033[0m" << std::endl;
    }


    // Error logger
    // 1 definition for logger with argument and one without
    template<typename... Args>
    void error(std::string ai_scope, std::string ai_msg, Args... args)
    {
      std::string w_str = ai_scope + " [ERROR] " + ai_msg;

      char w_buffer2[100];
      sprintf(w_buffer2, w_str.c_str(), args...);

      std::cout <<  "\033[31m" << w_buffer2 <<  "\033[0m" << std::endl;
    }

    void error(std::string ai_scope, std::string ai_msg)
    {
      std::string w_str = ai_scope + " [ERROR] " + ai_msg;
      std::cout <<  "\033[31m" <<w_str <<  "\033[0m" << std::endl;
    }


    // Info logger
    // 1 definition for logger with argument and one without
    template<typename... Args>
    void info(std::string ai_scope, std::string ai_msg, Args... args)
    {
      std::string w_str = ai_scope + " [INFO] " + ai_msg;

      char w_buffer2[100];
      sprintf(w_buffer2, w_str.c_str(), args...);

      std::cout << w_buffer2 << std::endl;
    }

    void info(std::string ai_scope, std::string ai_msg)
    {
      std::string w_str = ai_scope + " [INFO] " + ai_msg;
      std::cout << w_str << std::endl;
    }


    // Debug logger
    // 1 definition for logger with argument and one without
    template<typename... Args>
    void debug(std::string ai_scope, std::string ai_msg, Args... args)
    {
      std::string w_str = ai_scope + " [DEBUG] " + ai_msg;

      char w_buffer2[100];
      sprintf(w_buffer2, w_str.c_str(), args...);

      std::cout <<  "\033[36m" << w_buffer2 <<  "\033[0m" << std::endl;
    }

    void debug(std::string ai_scope, std::string ai_msg)
    {
      std::string w_str = ai_scope + " [DEBUG] " + ai_msg;
      std::cout <<  "\033[36m" << w_str <<  "\033[0m" << std::endl;
    }
};

static Logger logger;
}




#endif

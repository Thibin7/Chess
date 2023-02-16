#ifndef TESTTOOLS_H
#define TESTTOOLS_H

#include <string>
#include <vector>

namespace TestTools{

template <typename T>
bool isInVector(std::vector<T> ai_vector, T ai_value)
{
    typename std::vector<T>::iterator w_TIterator = ai_vector.begin();

    for (; w_TIterator != ai_vector.end(); w_TIterator++)
    {
      if ( *w_TIterator == ai_value )
      {
        return true;
      }
    }

    return false;
}


}

#endif

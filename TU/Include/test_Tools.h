#ifndef TESTTOOLS_H
#define TESTTOOLS_H

#include <string>
#include <vector>

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/Portability.h>

#include "../../Include/Board.h"

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
};

void _checkDefaultBoard(const std::string & ai_func, const unsigned int & ai_line, Board * ai_board);

void _checkDefaultMovement(const std::string & ai_func,
                                      const unsigned int & ai_line,
                                      Board * ai_board,
                                      const std::string ai_filePath,
                                      const PieceEnum ai_pieceType,
                                      const ColorEnum ai_pieceColor,
                                      const ts_position ai_startPiecePosition,
                                      const std::vector<ts_position> ai_validPiecePosition);

void _checkBlockedMovement(const std::string & ai_func,
                                      const unsigned int & ai_line,
                                      Board * ai_board,
                                      const PieceEnum ai_pieceType,
                                      const ColorEnum ai_pieceColor,
                                      const ts_position ai_startPiecePosition,
                                      const std::vector<ts_position> ai_blockedSquares);

void _checkCaptureMovement(const std::string & ai_func,
                                      const unsigned int & ai_line,
                                      Board * ai_board,
                                      const std::string ai_filePath,
                                      const PieceEnum ai_pieceType,
                                      const ColorEnum ai_pieceColor,
                                      const ts_position ai_startPiecePosition,
                                      const std::vector<ts_position> ai_otherPiecePosition);

void _checkPiece(const std::string & ai_func, const unsigned int & ai_line, Board * ai_board, const ts_position ai_piecePosition, const PieceEnum& ai_pieceType, const ColorEnum& ai_pieceColor);
void _checkSquareEmpty(const std::string & ai_func, const unsigned int & ai_line, Board * ai_board, const ts_position ai_position);
void _checkSquareTaken(const std::string & ai_func, const unsigned int & ai_line, Board * ai_board, const ts_position ai_position);
}

#endif

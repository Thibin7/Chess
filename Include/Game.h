#ifndef GAME_H
#define GAME_H

#include <vector>
#include <Piece.h>


// Game class
class Game
{
  public:
    Game();
    ~Game();

    void start();

  private:
    bool m_isGameStopped {false};

    ts_move _manageUserInput();
    void _help();


};

#endif

#include <stdio.h>
#include <iostream>
#include <string>

#include "../Include/Game.h"

int main(int argc, char * argv[])
{
  Game myGame;
  std::string w_filePath = "";

  // We load file given in entry
  if (argc == 2)
  {
    w_filePath = argv[1];
  }

  myGame.start(w_filePath);
}

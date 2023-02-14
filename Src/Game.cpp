#include "../Include/Game.h"
#include "../Include/Board.h"
#include "../Include/Constants.h"

// Constructor
Game::Game()
{}


// Destructor
Game::~Game()
{}

// Main method that run the game
void Game::start()
{
  Board * w_myBoard = new Board();
  w_myBoard->displayCurrentState();


  while (true)
  {
    // We ask the user about the move
    ts_move w_managedInput = _manageUserInput();

    // If the player want the game to end
    if (m_isGameStopped) break;

    // If the user input is valid we process the move
    if( w_managedInput != Constants::C_EOF_MOVE )
    {
        w_myBoard->processMove(w_managedInput.startPos, w_managedInput.endPos);
    }

    // Display the board
    w_myBoard->displayCurrentState();
  }

  if (w_myBoard != nullptr)
  {
    delete w_myBoard;
  }
}

// Manage the user input
ts_move Game::_manageUserInput()
{
    std::string w_userInput = "";
    ts_move w_askedMove = Constants::C_EOF_MOVE;

    std::cout << "Enter movement : ";
    std::cin >> w_userInput;

    // First we check if the user want to quit the Game
    if (w_userInput == "exit")
    {
      m_isGameStopped = true;
      return w_askedMove;
    }


    // Then we check the validity of the input string

    // If the elen of the string in not equal to 4
    if ( w_userInput.length() != 4 )
    {
      std::cout << "[Warning] Input given has not the good length" << std::endl;
      _help();

      return w_askedMove;
    }

    // We convert the first input to an int using ASCII soustraction
    int w_firstInput   = w_userInput[0] - 'a';
    int w_secondInput  = w_userInput[1] - 'a' + '0';
    int w_thirdInput   = w_userInput[2] - 'a';
    int w_fourthInput  = w_userInput[3] - 'a' + '0';

    // If the input given is not on the board
    if ( (abs(w_firstInput) > 7)
      || (abs(w_secondInput) > 7)
      || (abs(w_thirdInput) > 7)
      || (abs(w_fourthInput) > 7) )
    {
      std::cout << "[Warning] Bad input given. Not a valid Square !" << std::endl;
      _help();

      return w_askedMove;
    }

    // Set the move wanted by the player
    w_askedMove.startPos = {w_firstInput, w_secondInput};
    w_askedMove.endPos = {w_thirdInput, w_fourthInput};

    return w_askedMove;
}

void Game::_help()
{
  std::cout << std::endl << "###" << std::endl;
  std::cout << "You need to enter the square you want the piece to move from "
            << "then the square you want it to move to" << std::endl;
  std::cout << "The squares are represented by the coordonates ont the board" << std::endl;
  std::cout << "Exemple : 'Enter movement : a1b2'" << std::endl;

}

#include "Game.h"

using namespace std;

int main()
{
    // Seed the random number generator with the current time for randomization
    srand(static_cast<unsigned>(time(0)));

    // Ask the player to input their hero's name
    string playerName;
    cout << "Enter your hero's name: ";
    cin >> playerName;

    // Create an instance of the Game class with the player's name
    Game game(playerName);

    // Display the introductory story and wait for the player to press space to continue
    game.displayIntro();

    // Start the game, which will handle the level progression and gameplay
    game.startGame();

    // Return 0 to indicate successful execution
    return 0;
}
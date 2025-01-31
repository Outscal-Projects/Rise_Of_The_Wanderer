#ifndef GAME_H
#define GAME_H

#include "Player.h"  // Include the Player class to interact with the player object
#include "Enemy.h"   // Include the Enemy class for enemy interactions during the game
#include "Level.h"   // Include the Level class to manage the level and game progression

using namespace std;

// The Game class manages the overall game flow, including the player's journey, levels, and battles
class Game
{
    Player player;  // Declare a Player object to represent the player in the game

public:
    // Constructor to initialize the Game object with the player's name
    Game(const string &playerName);

    // Method to display the introductory story and set the stage for the player's journey
    void displayIntro();

    // Method to start the game, initializing the first level and handling the game progression
    void startGame();
};

#endif // GAME_H
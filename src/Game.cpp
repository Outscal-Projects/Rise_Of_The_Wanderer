#include "Game.h"

using namespace std;

// Constructor to initialize the Game object with a player's name
Game::Game(const string &playerName)
    : player(playerName) {}

// Display the introduction to the player, setting the stage for the story
void Game::displayIntro()
{
    Utility::waitForSpace("Welcome to Rise of the Wanderer!");
    Utility::waitForSpace("Our story begins in a peaceful village...");
    Utility::waitForSpace("One fateful night, the village was attacked by the monstrous Murlocs.");
    Utility::waitForSpace("Many were captured, and some lost their lives...");
    Utility::waitForSpace("You, the last hope of the village, must rise and defeat the evil Murlocs!");
    Utility::waitForSpace("To achieve this, you must venture through six perilous levels...");
    Utility::waitForSpace("...and gather the sacred items: Sword, Shield, Armor, and Bow.");
    Utility::waitForSpace("Only then can you face the final boss: Murloc the Devourer.");
    Utility::waitForSpace("Let's move forward and begin your journey...");
}

// Start the game, initialize the first level, and handle level progression
void Game::startGame()
{
    Utility::clearConsole(); // Clear the console to start fresh
    Utility::waitForSpace("Welcome, " + player.getName() + "! Your journey begins."); // Greet the player

    Level level(player); // Create a new Level object for the player
    level.handleLevel(); // Begin the first level and handle its progression
}
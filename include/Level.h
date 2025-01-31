#ifndef LEVEL_H
#define LEVEL_H

#include "Player.h"
#include "Enemy.h"

using namespace std;

class Level
{
private:
    int levelNumber;             // The number representing the current level
    int enemyCount;              // The number of enemies in the level
    vector<Enemy *> enemies;     // List of enemies in the level
    Player &player;              // Reference to the player, used throughout the level

public:
    // Constructor: Initializes the level with a reference to the player
    Level(Player &player);

    // Destructor: Cleans up any dynamically allocated enemies
    ~Level();

    // Main function to handle the flow of the level
    void handleLevel();

    // Starts the level, setting up necessary elements
    void startLevel();                 

    // Spawns enemies in the level
    void spawnEnemies();               

    // Checks if the level has been completed (checks for all enemies defeated)
    bool isLevelComplete() const;       

    // Handles the actions and rewards after completing a level
    void handleLevelCompletion();       

    // Manages the battle between the player and an individual enemy
    void battleWithEnemy(Enemy &enemy);

    // Handles player choices in the battle or scenario
    int HandleChoices(Enemy &enemy);

    // Starts a boss battle with a special set of mechanics
    void bossBattle(Enemy &enemy);
};

#endif // LEVEL_H
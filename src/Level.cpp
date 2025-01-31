#include "Level.h"

// Constructor: Initializes the level number and references the player
Level::Level(Player &player) : levelNumber(1), player(player) {}

// Function to spawn enemies dynamically based on the level number
void Level::spawnEnemies()
{
    enemyCount = levelNumber;

    // Spawn enemies with names like "Goblin1", "Goblin2", etc.
    for (int i = 0; i < enemyCount; ++i)
    {
        Enemy *enemy = new Enemy("Goblin" + to_string(i + 1), levelNumber); // Create new enemy with random stats
        enemies.push_back(enemy);  // Add the enemy to the level's enemy list
    }

    Utility::waitForSpace(to_string(levelNumber) + " Goblins have blocked path, defeat them and move forth!");
}

// Main function to handle the level's gameplay
void Level::handleLevel()
{
    // Run the level while the level number is less than or equal to 6 and the player is alive
    while (levelNumber <= 6 && player.isAlive())
    {
        startLevel();  // Start the current level

        if (player.isAlive())  // If the player is still alive, move to the next level
            ++levelNumber;
    }
}

// Function to handle the battles in the level
void Level::startLevel()
{
    // Indicate the start of the level
    Utility::waitForSpace("Level " + to_string(levelNumber) + " begins!");

    // Clear previous enemies from the previous level
    enemies.clear(); // Ensures no enemies from the previous level are reused

    if (levelNumber < 6)  // If the level number is less than 6, spawn regular enemies
    {
        spawnEnemies();  // Spawn Goblins for this level

        // Battle loop for all enemies in the current level
        for (size_t i = 0; i < enemies.size(); ++i)
        {
            Enemy *enemy = enemies[i];
            Utility::waitForSpace("A wild " + enemy->getName() + " comes forth to attack you!");
            battleWithEnemy(*enemy);  // Handle the battle with the current enemy
        }
    }
    else if (levelNumber == 6)  // If it's the final level (level 6), handle the boss battle
    {
        player.increaseSpecialAbilityChance();  // Give the player a chance to unlock all abilities

        // Spawn the boss enemy for level 6
        Enemy *boss = new Enemy("Murloc the Devourer", 6);
        boss->spawnBoss();  // Boss has special abilities

        bossBattle(*boss);  // Start the boss battle
    }

    // After all battles, check if the level is complete
    if (isLevelComplete())
        handleLevelCompletion();  // Handle rewards and progression to the next level
}

// Function to handle battle between player and enemy
void Level::battleWithEnemy(Enemy &enemy)
{
    while (player.isAlive() && enemy.isAlive())  // Continue until either the player or enemy is defeated
    {
        int choice = HandleChoices(enemy);  // Get the player's action choice

        if (choice == 3 || choice == 0)  // If the player chooses to check stats or makes an invalid choice, continue
            continue;

        if (!enemy.isAlive())  // If the enemy is defeated, exit the battle
        {
            Utility::waitForSpace(enemy.getName() + " is defeated!");
            break;
        }

        // The enemy attacks the player if it's still alive
        enemy.attack(player);

        if (!player.isAlive())  // If the player is defeated, exit the battle
        {
            Utility::waitForSpace(player.getName() + " has been defeated!");
            break;
        }
    }
}

// Function to handle the boss battle
void Level::bossBattle(Enemy &boss)
{
    Utility::waitForSpace("Final Boss: Murloc the Devourer appears!");

    while (player.isAlive() && boss.isAlive())  // Continue until the player or the boss is defeated
    {
        int choice = HandleChoices(boss);  // Handle player choice for attack, heal, or stats

        if (choice == 3 || choice == 0)  // If the player chooses to check stats or makes an invalid choice, continue
            continue;

        if (!boss.isAlive())  // If the boss is defeated, end the battle
        {
            Utility::waitForSpace("Murloc the Devourer is defeated! The village is saved!");
            return;
        }

        // The boss attacks the player
        boss.bossAttack(player);

        if (!player.isAlive())  // If the player is defeated, end the battle
        {
            Utility::waitForSpace(player.getName() + " has fallen... The village is lost...");
            return;
        }
    }
}

// Function to handle player choices in the battle
int Level::HandleChoices(Enemy &enemy)
{
    Utility::clearConsole();  // Clear the console for a fresh display
    cout << "========== Battle ==========\n";
    cout << "Level: " << levelNumber << "\n";
    cout << "\nPlayer: \n";
    cout << "Name: " << player.getName() << "\n";
    cout << "Health: " << player.getHealth() << "/" << player.getMaxHealth() << "\n";
    cout << "\nEnemy: \n";
    cout << "Name: " << enemy.getName() << "\n";
    cout << "Health: " << enemy.getHealth() << "/" << enemy.getMaxHealth() << "\n";
    cout << "============================\n";

    cout << "Choose your action:\n";
    cout << "1. Attack\n";
    cout << "2. Heal\n";
    cout << "3. Display Stats\n";
    cout << "Enter choice: ";

    int choice;
    cin >> choice;

    // Handle the player's choice
    switch (choice)
    {
    case 1:  // Player chooses to attack
        player.attack(enemy);
        return 1;
    case 2:  // Player chooses to heal
        player.heal();
        return 2;
    case 3:  // Player chooses to view stats
        player.getStats();
        enemy.getStats();
        Utility::waitForSpace("...");
        return 3;
    default:  // Invalid choice
        Utility::waitForSpace("Invalid choice! Please choose between 1-3 only.");
        return 0;
    }
}

// Function to check if all enemies in the level are defeated
bool Level::isLevelComplete() const
{
    for (const Enemy *enemy : enemies)
    {
        if (enemy->isAlive())
            return false;
    }
    return true;
}

// Function to handle level completion tasks
void Level::handleLevelCompletion()
{
    if (!isLevelComplete() || !player.isAlive())  // If the level is not complete or the player is dead, exit
        return;

    Utility::waitForSpace("Level " + to_string(levelNumber) + " completed!");

    player.levelUp();  // Level up the player after completing the level

    // Provide rewards and unlock abilities based on the level number
    switch (levelNumber)
    {
    case 1:  // Level 1 Completed
        player.addItem("Map");  // Give the player a map
        break;
    case 2:  // Level 2 Completed
        player.addItem("Sword");  // Give the player a sword
        player.unlockSpecialAbility(PlayerSpecialAbility::CRITICAL_HIT);  // Unlock Critical Hit ability
        break;
    case 3:  // Level 3 Completed
        player.addItem("Shield");  // Get this man shield
        player.unlockSpecialAbility(PlayerSpecialAbility::BLOCKER);  // Unlock Blocker ability
        break;
    case 4:  // Level 4 Completed
        player.addItem("Armour");  // Give the player armor
        player.unlockSpecialAbility(PlayerSpecialAbility::LIFE_STEAL);  // Unlock Life Steal ability
        break;
    case 5:  // Level 5 Completed
        player.addItem("Bow");
        player.unlockSpecialAbility(PlayerSpecialAbility::RANGED_ATTACK);  // Unlock Ranged Attack ability
        break;
    case 6:  // Level 6 Completed
        Utility::waitForSpace("Congratulations " + player.getName() + " you successfully defeated Murloc and freed the Village from its wrath...");
        break;
    }
}

// Destructor to clean up dynamically allocated enemies
Level::~Level()
{
    for (Enemy *enemy : enemies)
    {
        delete enemy;  // Free the memory allocated for each enemy
    }
    enemies.clear();  // Clear the vector holding the enemies
}
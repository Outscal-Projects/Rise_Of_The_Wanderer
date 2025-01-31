#ifndef PLAYER_H
#define PLAYER_H

#include "Character.h"  // Include the Character class for inheritance

// Enum class to represent the player's special abilities
enum class PlayerSpecialAbility
{
    NONE,            // No special ability
    CRITICAL_HIT,    // Critical Hit ability that doubles damage
    BLOCKER,         // Blocker ability that negates the next attack's damage
    LIFE_STEAL,      // Life Steal ability that recovers health based on damage dealt
    RANGED_ATTACK    // Ranged Attack ability that modifies ranged damage
};

using namespace std;

class Player : public Character  // The Player class inherits from Character class
{
private:
    int healPotion;  // Amount of health the player can recover from a heal potion
    vector<string> inventory;  // Inventory to store items
    vector<PlayerSpecialAbility> specialAbilities;  // List of unlocked special abilities

public:
    // Constructor to initialize a Player object with the given name and default stats
    Player(const string &name);

    // Getter for the player's current health
    int getHealth() const;

    // Override the attack function from the Character class to apply damage logic
    void attack(Character &target) override;

    // Method to heal the player using a heal potion
    void heal();

    // Method to add an item to the player's inventory
    void addItem(const string &item);

    // Method to get item from the player's inventory
    vector<string> getInventory() const;

    // Method to level up the player, increasing stats
    void levelUp();

    // Method to increase the special ability chance (usually tied to leveling up)
    void increaseSpecialAbilityChance();

    // Method to unlock a special ability for the player
    void unlockSpecialAbility(PlayerSpecialAbility ability);

    // Method to get a list of the player's unlocked special abilities in string form
    vector<string> getSpecialAbilities() const;

    // Method to check if the player has a specific special ability
    bool hasSpecialAbility(PlayerSpecialAbility ability) const;

    // Helper function to convert a PlayerSpecialAbility enum to a human-readable string
    static string specialAbilityToString(PlayerSpecialAbility ability);

    // Override the getStats function to display all the player's stats
    void getStats() const override;

    // Special Ability Effect methods
    void performCriticalHit(int &damage);  // Apply critical hit effect (double the damage)
    void performBlocker(int &damage);      // Apply blocker effect (negate damage)
    void performLifeSteal(int damage);    // Apply life steal effect (recover health)
    void performRangedAttack(int &damage); // Modify damage for ranged attacks
};

#endif // PLAYER_H
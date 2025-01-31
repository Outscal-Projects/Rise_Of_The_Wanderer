#ifndef ENEMY_H
#define ENEMY_H

#include "Character.h" // Include the base Character class, since Enemy is derived from it

// Enum class representing special abilities that an Enemy can have
enum class EnemySpecialAbility
{
    NONE,         // No special ability
    GROUND_SLASH, // A powerful ground attack
    SPEED_DASH,   // A quick movement attack
    HEALTH_REGEN  // Regenerates health
};

using namespace std;

// Enemy class, which inherits from Character
class Enemy : public Character
{
private:
    vector<EnemySpecialAbility> specialAbilities; // Stores the special abilities of the enemy

public:
    // Constructor that randomizes health and damage based on the level
    Enemy(const string &name, int level);

    // Getter for enemy's health
    int getHealth() const;

    // Enemy's attack behavior (overrides the pure virtual attack function in Character)
    void attack(Character &target) override;

    void spawnBoss();

    // Special attack function for boss enemies
    void bossAttack(Character &target);

    // Method to unlock a special ability for the enemy
    void unlockSpecialAbility(EnemySpecialAbility ability);

    // Checks if the enemy has a specific special ability
    bool hasSpecialAbility(EnemySpecialAbility ability) const;

    // Method to get a list of the player's unlocked special abilities in string form
    vector<string> getSpecialAbilities() const;

    // Helper function to convert a PlayerSpecialAbility enum to a human-readable string
    static string specialAbilityToString(EnemySpecialAbility ability);

    // Displays all enemy stats
    void getStats() const override;

    // Special Ability Effects
    void performGroundSlash(int &damage); // Increases damage with a ground-based attack
    void performSpeedDash(int &damage);   // Increases attack speed or movement speed
    void performHealthRegen(int &damage); // Allows the enemy to regain health
};

#endif // ENEMY_H
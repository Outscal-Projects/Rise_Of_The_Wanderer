#include "Character.h" // Include the header for the Character class

using namespace std;

// Constructor to initialize a Character object with specific attributes
Character::Character(const string &name, int health, int meleeDamage, int rangedDamage, int defense, int specialAbilityChance)
    : name(name), health(health), maxHealth(health), meleeDamage(meleeDamage), rangedDamage(rangedDamage), defense(defense), specialAbilityChance(specialAbilityChance) {}

// Method to take damage for the character
void Character::takeDamage(int damage)
{
    if (isBlockerActive)
    {
        damage = 0; // Prevent damage if Blocker is active
        Utility::waitForSpace(name + " blocks the attack! No damage taken.");
        isBlockerActive = false; // Reset Blocker after the next attack
    }
    else
    {
        // Reduce damage by defense, ensuring damage doesn't go below zero
        damage = max(0, damage - defense);

        // Subtract the resulting damage from the character's health
        health -= damage;

        // Ensure health doesn't go below zero
        if (health < 0)
            health = 0;

        // Display the damage taken and the remaining health
        Utility::waitForSpace(name + " takes " + to_string(damage) + " damage. Remaining health " + to_string(health) + "/" + to_string(maxHealth));
    }
}

// Method to check if the character is still alive (health > 0)
bool Character::isAlive() const { return health > 0; }

// Getter functions for encapsulation (to safely access private member variables)
string Character::getName() const { return name; }
int Character::getHealth() const { return health; }
int Character::getMaxHealth() const { return maxHealth; }
int Character::getMeleeDamage() const { return meleeDamage; }
int Character::getRangedDamage() const { return rangedDamage; }
int Character::getDefense() const { return defense; }
int Character::getSpecialAbilityChance() const { return specialAbilityChance; }
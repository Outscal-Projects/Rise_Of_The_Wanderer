#ifndef CHARACTER_H
#define CHARACTER_H

#include <Utility.h> // Include Utility.h for utility functions

using namespace std;

class Character
{
protected:
    string name;                  // Name of the character
    int health;                   // Current health of the character
    int maxHealth;                // Maximum health the character can have
    int meleeDamage;              // Melee damage the character can deal
    int rangedDamage;             // Ranged damage the character can deal
    int defense;                  // Defense points of the character (reduces incoming damage)
    int specialAbilityChance;     // Chance of performing a special ability (percentage)
    bool isBlockerActive = false; // Bool check for sheild

public:
    // Constructor to initialize the character with name and stats
    Character(const string &name, int health, int meleeDamage, int rangedDamage, int defense, int specialAbilityChance);

    // Virtual destructor (allows proper cleanup of derived class objects)
    virtual ~Character() {}

    // Pure virtual function for attack, which will be implemented in derived classes
    virtual void attack(Character &target) = 0;

    // Method to apply damage to the character
    virtual void takeDamage(int damage);

    // Method to check if the character is alive
    bool isAlive() const;

    // Getter functions for character stats (to access private members)
    string getName() const;                      // Get the character's name
    virtual int getHealth() const;               // Get current health (to be overridden if needed)
    virtual int getMaxHealth() const;            // Get max health (to be overridden if needed)
    virtual int getMeleeDamage() const;          // Get melee damage (to be overridden if needed)
    virtual int getRangedDamage() const;         // Get ranged damage (to be overridden if needed)
    virtual int getDefense() const;              // Get defense (to be overridden if needed)
    virtual int getSpecialAbilityChance() const; // Get special ability chance (to be overridden if needed)

    // Pure virtual function to display character stats (implemented in derived classes)
    virtual void getStats() const = 0;
};

#endif // CHARACTER_H
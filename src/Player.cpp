#include "Player.h"

using namespace std;

// Constructor to initialize Player with default stats
Player::Player(const string &name)
    : Character(name, 100, 15, 10, 3, 0) { healPotion = 20; }

// Getter for health value
int Player::getHealth() const { return health; }

// Increases special ability chance for the player
void Player::increaseSpecialAbilityChance() { specialAbilityChance = 10; }

// The player's attack function where a random choice between melee and ranged attack is made
void Player::attack(Character &target)
{
    int damage;

    // Randomly choose between melee or ranged damage
    if (rand() % 2 == 0)
    { // 50% chance for melee attack
        damage = meleeDamage;
        Utility::waitForSpace(name + " used Katana for moderate damage of " + to_string(damage) + "!");
    }
    else
    { // 50% chance for ranged attack
        damage = rangedDamage;
        Utility::waitForSpace(name + " used Kunai for low damage of " + to_string(damage) + "!");
    }

    // Check if the player has a special ability and apply it with a certain chance
    if (hasSpecialAbility(PlayerSpecialAbility::CRITICAL_HIT) && rand() % 100 < specialAbilityChance)
        performCriticalHit(damage); // Apply Critical Hit
    else if (hasSpecialAbility(PlayerSpecialAbility::BLOCKER) && rand() % 100 < specialAbilityChance)
        performBlocker(damage); // Activate Blocker (no damage on next attack)
    else if (hasSpecialAbility(PlayerSpecialAbility::LIFE_STEAL) && rand() % 100 < specialAbilityChance)
        performLifeSteal(damage); // Apply Life Steal (recover health)
    else if (hasSpecialAbility(PlayerSpecialAbility::RANGED_ATTACK))
        performRangedAttack(damage); // Apply Ranged Attack

    // Apply the damage to the target
    target.takeDamage(damage);
}

// Critical Hit doubles the damage
void Player::performCriticalHit(int &damage)
{
    damage *= 2;  // Double the damage
    Utility::waitForSpace(name + " activates Critical Hit! Damage is doubled!");
}

// Blocker ability prevents damage on the next attack
void Player::performBlocker(int &damage)
{
    isBlockerActive = true;  // Set flag to activate Blocker
    Utility::waitForSpace(name + " activates Blocker! Next attack will do no damage.");
}

// Life Steal ability heals the player for 25% of the damage dealt
void Player::performLifeSteal(int damage)
{
    int healthRecovered = damage / 4; // Recover 25% of the damage dealt
    health += healthRecovered;
    if (health > maxHealth)
        health = maxHealth; // Prevent exceeding max health
    Utility::waitForSpace(name + " activates Life Steal! Recovers " + to_string(healthRecovered) + " health.");
}

// Ranged Attack ability multiplies the ranged damage by 3 and prevents the next enemy attack from dealing damage
void Player::performRangedAttack(int &damage)
{
    damage = rangedDamage * 3;  // Increase damage for ranged attack
    Utility::waitForSpace(name + " activates Ranged Attack by using Bow! You will not take damage from the next enemy attack.");
}

// Heal function that restores health with the use of a potion
void Player::heal()
{
    health += healPotion;  // Heal by the amount of the potion
    if (health > maxHealth)
        health = maxHealth;  // Prevent health from exceeding max value
    Utility::waitForSpace(name + " heals. Current health: " + to_string(health));
}

// Add an item to the player's inventory
void Player::addItem(const string &item)
{
    inventory.push_back(item);  // Add item to inventory
    Utility::waitForSpace(name + " receives " + item);
}

// Getter for player's inventory
vector<string> Player::getInventory() const { return inventory; }

// Level up function to increase the player's stats
void Player::levelUp()
{
    maxHealth += 20;  // Increase max health
    health = maxHealth;  // Restore health to full
    healPotion += 5;  // Increase heal potion amount
    meleeDamage += 5;  // Increase melee damage
    rangedDamage += 3;  // Increase ranged damage
    defense += 2;  // Increase defense
    Utility::waitForSpace(name + " levels up! Stats increased.");
}

// Unlock a special ability for the player
void Player::unlockSpecialAbility(PlayerSpecialAbility ability)
{
    // Check if the ability is already unlocked
    if (find(specialAbilities.begin(), specialAbilities.end(), ability) == specialAbilities.end())
    {
        specialAbilities.push_back(ability);  // Add ability to the list
        Utility::waitForSpace(name + " unlocks the ability: " + specialAbilityToString(ability));
    }
    else
    {
        Utility::waitForSpace(name + " already has the ability: " + specialAbilityToString(ability));
    }
}

// Get a list of the player's unlocked special abilities
vector<string> Player::getSpecialAbilities() const
{
    vector<string> abilityNames;
    for (PlayerSpecialAbility ability : specialAbilities)
    {
        abilityNames.push_back(specialAbilityToString(ability));  // Convert each ability to string
    }
    return abilityNames;
}

// Check if the player has a specific special ability
bool Player::hasSpecialAbility(PlayerSpecialAbility ability) const
{
    // Check if the ability exists in the specialAbilities vector
    return find(specialAbilities.begin(), specialAbilities.end(), ability) != specialAbilities.end();
}

// Converts SpecialAbility enum to a human-readable string
string Player::specialAbilityToString(PlayerSpecialAbility ability)
{
    switch (ability)
    {
    case PlayerSpecialAbility::NONE:
        return "None";
    case PlayerSpecialAbility::CRITICAL_HIT:
        return "Critical Hit";
    case PlayerSpecialAbility::BLOCKER:
        return "Blocker";
    case PlayerSpecialAbility::LIFE_STEAL:
        return "Life Steal";
    case PlayerSpecialAbility::RANGED_ATTACK:
        return "Ranged Attack";
    default:
        return "Unknown Ability";
    }
}

// Display player's stats
void Player::getStats() const
{
    cout << "\nName: " << name << "\n"
         << "Health: " << health << "/" << maxHealth << "\n"
         << "Heal Potion: " << healPotion << "\n"
         << "Melee Damage: " << meleeDamage << "\n"
         << "Ranged Damage: " << rangedDamage << "\n"
         << "Defense: " << defense << "\n"
         << "Special Ability Chance: " << specialAbilityChance << "\n"
         << "Unlocked Abilities: ";

    vector<string> abilities = getSpecialAbilities(); // Get unlocked abilities

    if (abilities.empty())
        cout << "None"; // Display "None" if no abilities are unlocked
    else
    {
        for (size_t i = 0; i < abilities.size(); ++i)
        {
            cout << abilities[i];
            if (i < abilities.size() - 1)
                cout << ", ";
        }
    }

    // Display inventory items
    cout << "\nInventory: ";

    vector<string> items = getInventory(); // Get Player Inventory

    if (items.empty())
        cout << "None"; // Display "None" if no items are found
    else
    {
        for (size_t i = 0; i < items.size(); ++i)
        {
            cout << items[i];
            if (i < items.size() - 1)
                cout << ", ";
        }
    }

    cout << "\n\n";
}
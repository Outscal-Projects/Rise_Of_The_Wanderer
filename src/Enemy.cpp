#include "Enemy.h"

using namespace std;

// Constructor that randomizes health and damage based on the level
Enemy::Enemy(const string &name, int level)
    : Character(name, rand() % (50 + level * 10) + 40, rand() % (10 + level * 5) + 7, rand() % (10 + level * 2) + 5, rand() % (2 + level * 2) + 2, 10)
{
    // Randomizing health between 50 - 109 depending on each level
    // Randomizing melee damage between 10 - 39 depending on each level
    // Randomizing ranged damage between 5 - 21 depending on each level
}

int Enemy::getHealth() const { return health; }

// Method to handle enemy attack
void Enemy::attack(Character &target)
{
    int damage;
    Utility::waitForSpace(name + " attacks!");

    // Randomly choose between melee or ranged damage
    if (rand() % 2 == 0)
    { // 50% chance for melee attack
        damage = meleeDamage;
        Utility::waitForSpace("It's a melee attack!");
    }
    else
    { // 50% chance for ranged attack
        damage = rangedDamage;
        Utility::waitForSpace("It's a ranged attack!");
    }

    // Apply the calculated damage to the target
    target.takeDamage(damage);
}

// Method to set up a boss with stronger stats and abilities
void Enemy::spawnBoss()
{
    // Increase base stats for the boss
    health = 350;              // Boss has higher health
    maxHealth = 350;           // Boss has higher max health
    meleeDamage = 45;          // Stronger melee attack
    rangedDamage = 40;         // Stronger ranged attack
    defense = 35;              // Higher defense than normal enemies
    specialAbilityChance = 10; // Increased chance for special abilities

    // Unlock boss special abilities
    unlockSpecialAbility(EnemySpecialAbility::GROUND_SLASH);
    unlockSpecialAbility(EnemySpecialAbility::SPEED_DASH);
    unlockSpecialAbility(EnemySpecialAbility::HEALTH_REGEN);
}

// Method to handle the boss's attack
void Enemy::bossAttack(Character &target)
{
    int damage;
    Utility::waitForSpace(name + " attacks!");

    // Randomly choose between melee or ranged damage
    if (rand() % 2 == 0)
    { // 50% chance for melee attack
        damage = meleeDamage;
        Utility::waitForSpace("It's a powerful melee attack!");
    }
    else
    { // 50% chance for ranged attack
        damage = rangedDamage;
        Utility::waitForSpace("It's a powerful ranged attack!");
    }

    // Check for special abilities
    if (hasSpecialAbility(EnemySpecialAbility::GROUND_SLASH) && rand() % 100 < specialAbilityChance)
        performGroundSlash(damage);
    else if (hasSpecialAbility(EnemySpecialAbility::HEALTH_REGEN) && rand() % 100 < specialAbilityChance)
        performSpeedDash(damage);
    else if (hasSpecialAbility(EnemySpecialAbility::HEALTH_REGEN) && rand() % 100 < specialAbilityChance)
        performHealthRegen(damage);

    // Apply the calculated damage to the target
    target.takeDamage(damage);
}

// Method to perform Ground Slash (double damage)
void Enemy::performGroundSlash(int &damage)
{
    damage *= 2;
    Utility::waitForSpace(name + " activates Ground Slash! Damage is doubled!");
}

// Method to perform Speed Dash (block next attack)
void Enemy::performSpeedDash(int &damage)
{
    isBlockerActive = true;
    Utility::waitForSpace(name + " activates Speed Dash! Next attack will do no damage.");
}

// Method to regenerate health (heal by 20)
void Enemy::performHealthRegen(int &damage)
{
    int healthRecovered = 20; // Recover 50% of the damage dealt
    health += healthRecovered;
    if (health > maxHealth)
        health = maxHealth; // Prevent exceeding max health
    Utility::waitForSpace(name + " activates Health Regen! Recovers " + to_string(healthRecovered) + " health.");
}

// Method to unlock a special ability for the enemy
void Enemy::unlockSpecialAbility(EnemySpecialAbility ability)
{
    // If the ability is not already unlocked, add it to the list
    if (find(specialAbilities.begin(), specialAbilities.end(), ability) == specialAbilities.end())
    {
        specialAbilities.push_back(ability);
    }
}

// Method to check if the enemy has a specific special ability
bool Enemy::hasSpecialAbility(EnemySpecialAbility ability) const
{
    // Check if the ability exists in the specialAbilities vector
    return find(specialAbilities.begin(), specialAbilities.end(), ability) != specialAbilities.end();
}

// Method to get the list of special abilities
vector<string> Enemy::getSpecialAbilities() const
{
    vector<string> abilityNames;
    for (EnemySpecialAbility ability : specialAbilities)
    {
        abilityNames.push_back(specialAbilityToString(ability));
    }
    return abilityNames;
}

// Converts SpecialAbility enum to a human-readable string
string Enemy::specialAbilityToString(EnemySpecialAbility ability)
{
    switch (ability)
    {
    case EnemySpecialAbility::NONE:
        return "None";
    case EnemySpecialAbility::GROUND_SLASH:
        return "Ground Slash";
    case EnemySpecialAbility::SPEED_DASH:
        return "SSpeed Dash";
    case EnemySpecialAbility::HEALTH_REGEN:
        return "Health Regen";
    default:
        return "Unknown Ability";
    }
}

// Method to display enemy stats
void Enemy::getStats() const
{
    cout << "Name: " << name << "\n"
         << "Health: " << health << "/" << maxHealth << "\n"
         << "Melee Damage: " << meleeDamage << "\n"
         << "Ranged Damage: " << rangedDamage << "\n"
         << "Defense: " << defense << "\n"
         << "Special Ability Chance: " << specialAbilityChance << "\n"
         << "Unlocked Abilities: ";

    vector<string> abilities = getSpecialAbilities(); // Get unlocked abilities

    if (abilities.empty())
    {
        cout << "None"; // Display "None" if no abilities are unlocked
    }
    else
    {
        for (size_t i = 0; i < abilities.size(); ++i)
        {
            cout << abilities[i];
            if (i < abilities.size() - 1)
                cout << ", "; // Add comma between abilities
        }
    }

    cout << "\n\n";
}
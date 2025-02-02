// Author: ChatGPT
// For: Caleb Fowler Nick Luca
// Homework 2, Deliverable 1

#include <iostream>
#include <string>
#include <cassert>
#include <limits>
#include <iomanip>

using namespace std;

// Struct for simple data grouping
struct Stats {
    int health;
    int attack;
};

// Base class
class GameEntity {
protected:
    string name;
    Stats stats;
public:
    GameEntity(string n, int h, int a) : name(n) {
        stats.health = h;
        stats.attack = a;
    }
    virtual void display() const {
        cout << "| " << setw(10) << name << " | Health: "
            << setw(3) << stats.health << " | Attack: "
            << setw(3) << stats.attack << " |\n";
    }
    void heal(int amount) {
        assert(amount > 0); // Healing must be positive
        stats.health += amount;
        if (stats.health > 200) stats.health = 200; // Prevent exceeding max health
    }
    void takeDamage(int damage) {
        assert(damage >= 0); // Damage cannot be negative
        stats.health -= damage;
        if (stats.health < 0) stats.health = 0;
    }
    int getAttackPower() const { return stats.attack; }
    int getHealth() const { return stats.health; }
    string getName() const { return name; }
};

// Derived class (Enemy)
class Enemy : public GameEntity {
public:
    Enemy(string n, int h, int a) : GameEntity(n, h, a) {}
};

// Derived class (Player)
class Player : public GameEntity {
public:
    Player(string n, int h, int a) : GameEntity(n, h, a) {}

    void attack(GameEntity& target) {
        cout << name << " attacks " << target.getName() << " for " << stats.attack << " damage!\n";
        target.takeDamage(stats.attack);
    }
};

// Derived class (Ally)
class Ally : public GameEntity {
public:
    Ally(string n, int h, int a) : GameEntity(n, h, a) {}
};

// Dynamic array management
void resizeArray(GameEntity**& arr, int& size, int newSize) {
    assert(newSize > 0); // Ensure valid array size
    GameEntity** newArr = new GameEntity * [newSize];
    for (int i = 0; i < size && i < newSize; ++i) {
        newArr[i] = arr[i];
    }
    delete[] arr;
    arr = newArr;
    size = newSize;
}

// Function to validate integer input
int getValidatedInput(const string& prompt, int min, int max) {
    int value;
    while (true) {
        cout << prompt;
        cin >> value;
        if (cin.fail() || value < min || value > max) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number between " << min << " and " << max << ".\n";
        }
        else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore remaining input
            return value;
        }
    }
}

// Main function
int main() {
    // Greeting and initialization
    cout << "==================================\n";
    cout << " Welcome to the Battle Game! \n";
    cout << " In this game, you play as a hero battling against monsters!\n";
    cout << " Created by: Caleb Fowler Nick Luca \n";
    cout << "==================================\n";

    // User input validation
    string playerName;
    cout << "Enter player name: ";
    while (true) {
        getline(cin, playerName);
        if (!playerName.empty()) break;
        cout << "Player name cannot be empty. Try again: ";
    }

    int playerHealth = getValidatedInput("Enter player health (50-200): ", 50, 200);
    int playerAttack = getValidatedInput("Enter player attack power (5-50): ", 5, 50);

    int size = 2;
    GameEntity** entities = new GameEntity * [size];
    entities[0] = new Player(playerName, playerHealth, playerAttack);
    entities[1] = new Enemy("Goblin", 50, 10);

    // Resize array to accommodate an ally
    resizeArray(entities, size, 3);
    entities[2] = new Ally("Knight", 75, 20);

    // Heal player for demonstration
    static_cast<Player*>(entities[0])->heal(30);

    // Player attacks enemy for demonstration
    static_cast<Player*>(entities[0])->attack(*entities[1]);

    // Display game entities
    cout << "\nGame Entities:\n";
    cout << "----------------------------------\n";
    cout << "| Name      | Health | Attack |\n";
    cout << "----------------------------------\n";
    for (int i = 0; i < size; ++i) {
        entities[i]->display();
    }
    cout << "----------------------------------\n";

    // Clean up
    for (int i = 0; i < size; ++i) {
        delete entities[i];
    }
    delete[] entities;
    return 0;
}
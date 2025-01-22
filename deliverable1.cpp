// Author: ChatGPT
// For: Caleb Fowler
// Homework 1, Deliverable 1

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>

using namespace std;

// Singleton class for random number generation
class RandomNumberGenerator {
private:
    static RandomNumberGenerator* instance;
    RandomNumberGenerator() { srand(time(nullptr)); }

public:
    static RandomNumberGenerator* getInstance() {
        if (instance == nullptr) {
            instance = new RandomNumberGenerator();
        }
        return instance;
    }

    int getRandomNumber(int min, int max) {
        return min + rand() % (max - min + 1);
    }
};
RandomNumberGenerator* RandomNumberGenerator::instance = nullptr;

// Function prototypes
void displayGreeting();
int displayMenu();
void handleMenuOption(int option);
void displayTable(int scores[], int size);
bool promptYesNo(const string& message);
int getValidatedInput(const string& prompt, int min, int max);

int main() {
    displayGreeting();

    bool keepRunning = true;
    while (keepRunning) {
        int option = displayMenu();
        handleMenuOption(option);

        keepRunning = promptYesNo("Would you like to run the program again? (Y/N): ");
    }

    cout << "\nThank you for using the program. Goodbye!\n";
    return 0;
}

void displayGreeting() {
    cout << "============================================\n";
    cout << " Welcome to the Game Management Program!\n";
    cout << " Author: Caleb Fowler\n";
    cout << "============================================\n\n";
}

int displayMenu() {
    cout << "Select an option:\n";
    cout << "1. Display Player Scores\n";
    cout << "2. Generate Random Player Scores\n";
    cout << "3. Calculate Average Score\n";
    cout << "4. Quit\n";

    return getValidatedInput("Enter your choice (1-4): ", 1, 4);
}

void handleMenuOption(int option) {
    const int size = 5;
    int* scores = new int[size] {85, 90, 78, 92, 88};

    switch (option) {
    case 1:
        displayTable(scores, size);
        break;
    case 2: {
        RandomNumberGenerator* rng = RandomNumberGenerator::getInstance();
        for (int i = 0; i < size; ++i) {
            scores[i] = rng->getRandomNumber(50, 100);
        }
        displayTable(scores, size);
        break;
    }
    case 3: {
        int total = 0;
        for (int i = 0; i < size; ++i) {
            total += scores[i];
        }
        double average = static_cast<double>(total) / size;
        cout << "\nThe average score is: " << fixed << setprecision(2) << average << "\n\n";
        break;
    }
    case 4:
        cout << "Exiting the program.\n";
        break;
    }

    delete[] scores;
}

void displayTable(int scores[], int size) {
    cout << "\n---------------------------------------------\n";
    cout << "| Player Index | Player Score              |\n";
    cout << "---------------------------------------------\n";

    for (int i = 0; i < size; ++i) {
        cout << "| " << setw(12) << i + 1 << " | " << setw(26) << scores[i] << " |\n";
    }

    cout << "---------------------------------------------\n\n";
}

bool promptYesNo(const string& message) {
    char input;
    do {
        cout << message;
        cin >> input;
        input = toupper(input);
    } while (input != 'Y' && input != 'N');

    return input == 'Y';
}

int getValidatedInput(const string& prompt, int min, int max) {
    int input;
    while (true) {
        cout << prompt;
        cin >> input;
        if (cin.fail() || input < min || input > max) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please try again.\n";
        }
        else {
            return input;
        }
    }
}

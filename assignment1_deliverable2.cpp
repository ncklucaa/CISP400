// Author: Caleb Fowler Nick Luca
// Improvements to ChatGPT
// Homework 1, Deliverable 2

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>

using namespace std;

class RandNumGen
{
public:
    RandNumGen() { srand(static_cast<int>(time(nullptr))); }

    int getRandNum(int min, int max)
    {
        return min + rand() % (max - min + 1);
    }
};

void displayGreeting();
void showTable(int scores[], int size);
int displayMenu();
int getValidInput(const string& msg, int min, int max);
bool handleMenuOptions(int option, int* scores, int size);
bool userYesNo(const string& message);

void displayGreeting()
{
    cout << "============================================" << endl;
    cout << "Random Scores Program" << endl;;
    cout << "Author: Nick Luca" << endl;
    cout << "============================================" << '\n' << endl;

}

void showTable(int scores[], int size)
{
    cout << "\n---------------------------------------------" << endl;
    cout << "| Player Number |       Player Score        |" << endl;
    cout << "---------------------------------------------" << endl;

    for (int i = 0; i < size; i++)
    {
        cout << "| " << setw(12) << i + 1 << " | " << setw(26) << scores[i] << " | " << endl;
    }

    cout << "---------------------------------------------\n" << endl;
}

int displayMenu()
{
    cout << "Please select one of the menu options:" << '\n' << endl;
    cout << "1. Show Player Scores" << endl;
    cout << "2. Generate Random Player Scores" << endl;
    cout << "3. Calculate The Average Player Score" << endl;
    cout << "4. Quit The Program" << '\n' << endl;

    return getValidInput("Enter your choice (1-4): ", 1, 4);
}

int getValidInput(const string& msg, int min, int max)
{
    int userInput;
    while (true)
    {
        cout << msg;
        cin >> userInput;
        if (cin.fail() || userInput < min || userInput > max)
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input. Please try again." << endl;
        }
        else
        {
            return userInput;
        }
    }
}

bool handleMenuOptions(int option, int* scores, int size)
{
    switch (option)
    {
    case 1:
        showTable(scores, size);
        return true;
    case 2:
    {
        RandNumGen random;
        for (int i = 0; i < size; i++)
        {
            scores[i] = random.getRandNum(50, 100);
        }
        showTable(scores, size);
        return true;
    }
    case 3:
    {
        int total = 0;
        for (int i = 0; i < size; i++)
        {
            total += scores[i];
        }
        double average = static_cast<double>(total) / size;
        cout << "\nThe average player score is: " << fixed << setprecision(2) << average << " points" << "\n" << endl;
        return true;
    }
    case 4:
        cout << "Exiting the program" << '\n' << endl;
        return false;
    default:
        return true;
    }
}

bool userYesNo(const string& message)
{
    char userInput;
    do
    {
        cout << message;
        cin >> userInput;
        userInput = toupper(userInput);
    } while (userInput != 'Y' && userInput != 'N');

    return userInput == 'Y';
}

int main()
{
    const int size = 5;
    int* scores = new int[size];

    srand(static_cast<int>(time(0)));

    for (int i = 0; i < size; i++)
    {
        scores[i] = rand() % 100;
    }

    displayGreeting();

    bool keepRunning = true;
    while (keepRunning)
    {
        int option = displayMenu();
        keepRunning = handleMenuOptions(option, scores, size);

        if (keepRunning)
        {
            keepRunning = userYesNo("Would you like to run the program again? (Y/N): ");
        }
    }

    delete[] scores;

    cout << "\nThank you for using the program" << endl;
    cout << "Have a good day!" << endl;

    return 0;
}
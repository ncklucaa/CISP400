// Author: ChatGPT
// For: Caleb Fowler Nick Luca
// Homework 5, Deliverable 1

#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <limits>
using namespace std;

// Abstract Base Class
class TrainingDay {
public:
    virtual void input() = 0;
    virtual void display() const = 0;
    virtual ~TrainingDay() {}
    friend istream& operator>>(istream& in, TrainingDay& day) {
        day.input();
        return in;
    }
    friend ostream& operator<<(ostream& out, const TrainingDay& day) {
        day.display();
        return out;
    }
};

// StrengthDay (Child)
class StrengthDay : public TrainingDay {
private:
    string muscleGroup;
    int sets;
    int reps;
public:
    void input() override {
        cout << "Enter muscle group: ";
        getline(cin, muscleGroup);
        while (true) {
            cout << "Enter number of sets (1-10): ";
            cin >> sets;
            if (cin.fail() || sets < 1 || sets > 10) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Try again.\n";
            }
            else break;
        }
        while (true) {
            cout << "Enter number of reps (1-50): ";
            cin >> reps;
            if (cin.fail() || reps < 1 || reps > 50) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Try again.\n";
            }
            else break;
        }
        cin.ignore();
    }

    void display() const override {
        cout << left << setw(20) << "Strength" << setw(20) << muscleGroup << setw(10) << sets << setw(10) << reps << endl;
    }
};

// CardioDay (Child)
class CardioDay : public TrainingDay {
private:
    string cardioType;
    int duration; // minutes
public:
    void input() override {
        cout << "Enter cardio type: ";
        getline(cin, cardioType);
        while (true) {
            cout << "Enter duration in minutes (10-120): ";
            cin >> duration;
            if (cin.fail() || duration < 10 || duration > 120) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Try again.\n";
            }
            else break;
        }
        cin.ignore();
    }

    void display() const override {
        cout << left << setw(20) << "Cardio" << setw(20) << cardioType << setw(10) << duration << "min" << endl;
    }
};

// MealPrep class
class MealPrep {
private:
    string meal;
    int calories;
public:
    MealPrep(string s = "", int c = 0) : meal(s), calories(c) {}
    MealPrep(string str) {
        istringstream ss(str);
        getline(ss, meal, ',');
        ss >> calories;
    }
    operator string() const {
        ostringstream ss;
        ss << meal << "," << calories;
        return ss.str();
    }

    friend istream& operator>>(istream& in, MealPrep& mp) {
        cout << "Enter meal name: ";
        getline(in, mp.meal);
        cout << "Enter calorie amount: ";
        in >> mp.calories;
        in.ignore();
        return in;
    }
    friend ostream& operator<<(ostream& out, const MealPrep& mp) {
        out << "Meal: " << mp.meal << ", Calories: " << mp.calories << endl;
        return out;
    }
    int getCalories() const { return calories; }
};

// UserPlan aggregates dynamic TrainingDay* and composes MealPrep
class UserPlan {
private:
    TrainingDay** days;
    int size;
    int capacity;
    MealPrep meal;

    void resize(int newCap) {
        TrainingDay** newArr = new TrainingDay * [newCap];
        for (int i = 0; i < size; ++i)
            newArr[i] = days[i];
        delete[] days;
        days = newArr;
        capacity = newCap;
    }

public:
    UserPlan() : days(new TrainingDay* [2]), size(0), capacity(2) {}
    ~UserPlan() {
        for (int i = 0; i < size; ++i)
            delete days[i];
        delete[] days;
    }

    void addDay(TrainingDay* day) {
        if (size == capacity)
            resize(capacity * 2);
        days[size++] = day;
    }

    void inputPlan() {
        int num;
        cout << "\nHow many training days do you want to enter? ";
        cin >> num;
        cin.ignore();
        for (int i = 0; i < num; ++i) {
            cout << "\nEnter 1 for Strength or 2 for Cardio: ";
            int choice;
            cin >> choice;
            cin.ignore();
            if (choice == 1) addDay(new StrengthDay());
            else addDay(new CardioDay());
            cin >> *days[size - 1];
        }
        cout << "\nNow enter your meal prep info:\n";
        cin >> meal;
    }

    void showPlan() const {
        cout << "\n================ Weekly Plan Summary ================\n";
        cout << left << setw(20) << "Type" << setw(20) << "Target" << setw(10) << "Value1" << setw(10) << "Value2" << endl;
        cout << "----------------------------------------------------\n";
        for (int i = 0; i < size; ++i)
            cout << *days[i];
        cout << "----------------------------------------------------\n";
        cout << meal;
    }

    int getTotalCalories() const { return meal.getCalories(); }
};

int main() {
    cout << "==============================================\n";
    cout << "  Virtual Personal Trainer Plan Builder\n";
    cout << "  Created by: Nick Luca and ChatGPT\n";
    cout << "==============================================\n";

    UserPlan plan;
    plan.inputPlan();

    // Lambda to evaluate goal alignment
    auto checkGoal = [](int consumed, int goal) {
        return consumed >= goal ? "Goal met!" : "More calories needed.";
        };

    plan.showPlan();

    int goal = 2200;
    cout << "\nCalorie Goal Check (Goal: " << goal << "): ";
    cout << checkGoal(plan.getTotalCalories(), goal) << endl;

    return 0;
}
// Author: Caleb Fowler Nick Luca
// Improvements to ChatGPT
// Homework 5, Deliverable 2

#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <limits>
#include <cmath>
using namespace std;

class WorkoutSplit
{
public:
    virtual void displaySplit() const = 0;
    virtual string getName() const = 0;
    virtual ~WorkoutSplit() {}
};

class PushDay : public WorkoutSplit
{
public:
    void displaySplit() const override
    {
        cout << "Push Day:\n";
        cout << "- Incline Bench Press: 3x6-8\n";
        cout << "- Flat Dumbbell Press: 3x6-8\n";
        cout << "- Pec Deck Machine: 3x8-12\n";
        cout << "- Shoulder Press: 2x6-8\n";
        cout << "- Lateral Raises: 3x8-12\n";
        cout << "- JM Press: 3x6-8\n";
        cout << "- One-Hand Tricep Pushdown: 3x8-12\n\n";
    }
    string getName() const override { return "Push Day"; }
};

class PullDay : public WorkoutSplit
{
public:
    void displaySplit() const override
    {
        cout << "Pull Day:\n";
        cout << "- Lat Pulldown: 3x6-10\n";
        cout << "- T-Bar Rows: 3x6-10\n";
        cout << "- One Arm Cable Row: 3x6-10\n";
        cout << "- Reverse Pec Deck (Rear Delt): 3x10-15\n";
        cout << "- Preacher Curls: 3x8-10\n";
        cout << "- Cable Hammer Curls: 3x8-12\n\n";
    }
    string getName() const override { return "Pull Day"; }
};

class LegDay : public WorkoutSplit
{
public:
    void displaySplit() const override
    {
        cout << "Leg Day:\n";
        cout << "- RDLs: 3x8-10\n";
        cout << "- Hack Squats: 3x6-10\n";
        cout << "- Leg Extensions: 3x8-12\n";
        cout << "- Leg Curls: 3x8-12\n";
        cout << "- Adductors: 2x10-15\n";
        cout << "- Calf Raises: 4x10-15\n\n";
    }
    string getName() const override { return "Leg Day"; }
};

class UpperDay : public WorkoutSplit
{
public:
    void displaySplit() const override
    {
        cout << "Upper Day:\n";
        cout << "- Incline Smith: 3x6-8\n";
        cout << "- Lat Pulldown: 3x6-10\n";
        cout << "- T-Bar Row: 3x6-8\n";
        cout << "- Preacher Curls: 3x8-10\n";
        cout << "- Tricep Pushdown: 3x8-10\n";
        cout << "- Cable Lateral Raises: 3x8-12\n\n";
    }
    string getName() const override { return "Upper Day"; }
};

class LowerDay : public WorkoutSplit
{
public:
    void displaySplit() const override
    {
        cout << "Lower Day:\n";
        cout << "- RDLs: 3x8-10\n";
        cout << "- Hack Squat: 3x6-8\n";
        cout << "- Leg Extension: 3x8-12\n";
        cout << "- Leg Curls: 3x8-12\n";
        cout << "- Calf Raises: 4x10-15\n\n";
    }
    string getName() const override { return "Lower Day"; }
};

class ArmDay : public WorkoutSplit
{
public:
    void displaySplit() const override
    {
        cout << "Arm Day:\n";
        cout << "- Bayesian Curls: 3x6-10\n";
        cout << "- Preacher Curls: 3x6-10\n";
        cout << "- Cable Hammer Curls: 3x8-12\n";
        cout << "- JM Press: 3x6-8\n";
        cout << "- Overhead Cable Extension: 3x8-10\n";
        cout << "- Single Hand Pushdown: 3x8-12\n\n";
    }
    string getName() const override { return "Arm Day"; }
};

class ChestBackDay : public WorkoutSplit
{
public:
    void displaySplit() const override
    {
        cout << "Chest and Back Day:\n";
        cout << "- Incline Smith: 3x6-8\n";
        cout << "- Flat Dumbbell Press: 3x6-8\n";
        cout << "- Pec Dec Machine: 3x8-12\n";
        cout << "- Lat Pulldown: 3x6-10\n";
        cout << "- T-Bar Rows: 3x6-8\n";
        cout << "- Cable Rows: 3x6-10\n\n";
    }
    string getName() const override { return "Chest and Back Day"; }
};

class FullBodyDay : public WorkoutSplit
{
public:
    void displaySplit() const override
    {
        cout << "Full Body Day:\n";
        cout << "- Incline Smith: 3x6-8\n";
        cout << "- Lat Pulldown: 3x8-10\n";
        cout << "- Cable Lateral Raises: 3x8-12\n";
        cout << "- Leg Press: 3x6-8\n";
        cout << "- RDLs: 3x8-10\n\n";
    }
    string getName() const override { return "Full Body Day"; }
};

class WorkoutProgram 
{
private:
    WorkoutSplit** plans;
    int size;
public:
    WorkoutProgram(int days) : size(days) 
    {
        plans = new WorkoutSplit * [size];

        if (days == 1) 
        {
            plans[0] = new FullBodyDay();
        }
        else if (days == 2) 
        {
            plans[0] = new UpperDay();
            plans[1] = new LowerDay();
        }
        else if (days == 3) 
        {
            plans[0] = new PushDay();
            plans[1] = new PullDay();
            plans[2] = new LegDay();
        }
        else if (days == 4) 
        {
            plans[0] = new UpperDay();
            plans[1] = new LowerDay();
            plans[2] = new UpperDay();
            plans[3] = new LowerDay();
        }
        else if (days == 5) 
        {
            plans[0] = new PushDay();
            plans[1] = new PullDay();
            plans[2] = new LegDay();
            plans[3] = new UpperDay();
            plans[4] = new LowerDay();
        }
        else if (days >= 6) 
        {
            plans[0] = new PushDay();
            plans[1] = new PullDay();
            plans[2] = new LegDay();
            plans[3] = new PushDay();
            plans[4] = new PullDay();
            plans[5] = new LegDay();
            if (days == 7) 
            {
                plans[6] = new FullBodyDay(); // or reuse one of the above
            }
        }
    }

    ~WorkoutProgram() 
    {
        for (int i = 0; i < size; ++i)
            delete plans[i];
        delete[] plans;
    }

    void displaySplit() const 
    {
        cout << "\n================== Weekly Workout Plan ==================\n\n";
        for (int i = 0; i < size; ++i)
        {
            plans[i]->displaySplit();
        }
    }

    void displayTable() const
    {
        cout << "\n================ Workout Plan Summary Table ================\n";
        cout << "+--------+---------------------+\n";
        cout << "|  Day   |     Workout Split    |\n";
        cout << "+--------+---------------------+\n";
        for (int i = 0; i < size; ++i)
        {
            cout << "|   " << setw(2) << i + 1 << "   | " << setw(20) << left << plans[i]->getName() << "|\n";
        }
        cout << "+--------+---------------------+\n";
    }
};

class FitnessGoal 
{
private:
    string goal;
public:
    FitnessGoal() : goal("maintain") {}
    FitnessGoal(string g) : goal(g) {}
    operator string() const { return goal; }

    bool operator==(const string& other) const 
    {
        return goal == other;
    }

    friend istream& operator>>(istream& in, FitnessGoal& fg) 
    {
        while (true) 
        {
            cout << "Enter your goal (lose/maintain/gain): ";
            getline(in, fg.goal);
            if (fg.goal == "lose" || fg.goal == "maintain" || fg.goal == "gain") break;
            cout << "Invalid input. Please enter 'lose', 'maintain', or 'gain'.\n";
        }
        return in;
    }

    friend ostream& operator<<(ostream& out, const FitnessGoal& fg) 
    {
        out << fg.goal;
        return out;
    }
};

class UserProfile 
{
private:
    int age;
    double heightCm;
    double weightLbs;
    string sex;
    FitnessGoal goal;
public:
    void input() 
    {
        cout << "Enter your age: ";
        cin >> age;
        cout << "Enter your height in cm: ";
        cin >> heightCm;
        cout << "Enter your weight in lbs: ";
        cin >> weightLbs;
        cin.ignore();
        while (true) 
        {
            cout << "Enter your biological sex (m/f): ";
            getline(cin, sex);
            if (sex == "m" || sex == "f") break;
            cout << "Invalid input. Please enter 'm' or 'f'.\n";
        }
        cin >> goal;
    }

    double calculateCalories() const 
    {
        double weightKg = weightLbs / 2.20462;
        double bmr;
        if (sex == "m")
        {
            bmr = 10 * weightKg + 6.25 * heightCm - 5 * age + 5;
        }
        else
        {
            bmr = 10 * weightKg + 6.25 * heightCm - 5 * age - 161;
        }

        if (goal == "lose") { return bmr * 1.2; }
        if (goal == "gain") { return bmr * 1.6; }
        return bmr * 1.4;
    }

    int getProtein() const { return static_cast<int>(weightLbs); }
    string getGoal() const { return static_cast<string>(goal); }
};

int main() 
{
    cout << "==============================================\n";
    cout << "  Virtual Personal Trainer Plan Builder\n";
    cout << "  Created by: Nick Luca\n";
    cout << "==============================================\n";

    int days;
    while (true) 
    {
        cout << "\nHow many days per week can you work out? (1-7): ";
        cin >> days;
        if (cin.fail() || days < 1 || days > 7) 
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Try again.\n";
        }
        else break;
    }

    if (days == 7) 
    {
        cout << "\nNote: You should have at least one rest day per week to let your body recover. Consider making one of those an active recovery/cardio day.\n";
    }

    cin.ignore();
    char showProgram;
    cout << "\nWould you like to see your workout program? (y/n): ";
    cin >> showProgram;
    cin.ignore();

    if (showProgram == 'y' || showProgram == 'Y') 
    {
        WorkoutProgram program(days);
        program.displaySplit();
        program.displayTable();
    }

    UserProfile user;
    user.input();

    double calories = user.calculateCalories();
    int protein = user.getProtein();

    cout << "\n----------------- Nutrition Recommendation -----------------\n\n";
    cout << "Goal: " << user.getGoal() << endl;
    cout << "Calories/day: " << static_cast<int>(calories) << endl;
    cout << "Protein/day: " << protein << "g\n";

    auto weeklyProtein = [](int dailyProtein)
        {
            return dailyProtein * 7;
        };

    cout << "Weekly Protein Goal: " << weeklyProtein(protein) << "g\n";
    cout << "============================================================\n";

    return 0;
}
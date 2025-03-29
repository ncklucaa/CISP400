// Author: Caleb Fowler Nick Luca
// Improvements to ChatGPT
// Homework 4, Deliverable 2

#include <iostream>
#include <iomanip>
#include <limits>

using namespace std;

void greet();

class User
{
private:
    float kg;
    float cm;

public:
    User(float w = 0, float h = 0) : kg(w), cm(h) {}

    User(int w, int h)
    {
        kg = static_cast<float>(w);
        cm = static_cast<float>(h);
    }

    friend ostream& operator<<(ostream& os, const User& profile)
    {
        os << "Weight: " << profile.kg << " kg, Height: " << profile.cm << " cm";

        return os;
    }

    friend istream& operator>>(istream& is, User& profile)
    {
        is >> profile.kg >> profile.cm;

        return is;
    }

    float getWeight() const { return kg; }
    float getHeight() const { return cm; }
};

class Workout 
{
private:
    int mins;
    float intensity;

public:
    Workout(int min = 0, float inten = 1.0) : mins(min), intensity(inten) {}

    // Convert constructor to/from int (minutes)
    Workout(int min) : mins(min), intensity(1.0) {}

    friend ostream& operator<<(ostream& os, const Workout& workout) 
    {
        os << "Duration: " << workout.mins << " min, Intensity: " << workout.intensity;

        return os;
    }

    friend istream& operator>>(istream& is, Workout& workout) 
    {
        is >> workout.mins >> workout.intensity;

        return is;
    }

    int getMinutes() const { return mins; }
    float getIntensity() const { return intensity; }
};

class CalorieCalculator 
{
public:
    float operator()(const User& profile, const Workout& workout) 
    {
        float caloriesBurned = workout.getMinutes() * workout.getIntensity() * 0.07 * profile.getWeight();

        return caloriesBurned;
    }
};

class WorkoutLog 
{
private:
    Workout* workouts;
    int size;
    int capacity;

    void resize(int newCapacity) 
    {
        Workout* newWorkouts = new Workout[newCapacity];

        for (int i = 0; i < size; ++i) 
        {
            newWorkouts[i] = workouts[i];
        }
        delete[] workouts;
        workouts = newWorkouts;
        capacity = newCapacity;
    }

public:
    WorkoutLog(int cap = 5) : size(0), capacity(cap) 
    {
        workouts = new Workout[capacity];
    }

    ~WorkoutLog() 
    {
        delete[] workouts;
    }

    void addWorkout(const Workout& workout) 
    {
        if (size == capacity) 
        {
            resize(capacity * 2);
        }
        workouts[size++] = workout;
    }

    void showTotal(const User& user) const
    {
        cout << '\n';
        cout << "-----------------------------------------------\n";
        cout << "| No | Duration | Intensity | Calories Burned |\n";
        cout << "-----------------------------------------------\n";

        CalorieCalculator calc;
        float totalCals = 0.0;
        float totalInt = 0.0;
        int totalMins = 0;

        for (int i = 0; i < size; ++i) 
        {
            float cals = calc(user, workouts[i]);
            totalCals += cals;
            totalInt += workouts[i].getIntensity();
            totalMins += workouts[i].getMinutes();

            cout << "| " << setw(2) << i + 1 << " | " << setw(8) << workouts[i].getMinutes() << " | " << setw(9) << fixed << setprecision(1) << workouts[i].getIntensity()
                << " | " << setw(14) << fixed << setprecision(2) << cals << "  |\n";
        }

        float avgInt;
        if (size > 0)
        {
            avgInt = totalInt / size;
        }
        else
        {
            avgInt = 0;
        }

        cout << "-----------------------------------------------\n";
        cout << "|          Total Calories Burned: " << setw(10) << fixed << setprecision(2) << totalCals << '\n';
        cout << "|                  Total Minutes: " << setw(10) << totalMins << '\n';
        cout << "|              Average Intensity: " << setw(10) << fixed << setprecision(2) << avgInt << '\n';
        cout << "-----------------------------------------------\n";

        if (totalCals >= 550)
        {
            cout << "Hell yeah! You burned off a double double from In-N-Out\n";
        }
        else if (totalCals >= 250)
        {
            cout << "Solid effort!\n";
        }
        else
        {
            cout << "Good start every calorie burned off counts!\n";
        }
    }
};

class BMI
{
private:
    float val;

public:
    BMI(const User& user)
    {
        float hM = user.getHeight() / static_cast<float>(100.0);
        val = user.getWeight() / (hM * hM);
    }

    operator float() const { return val; }

    string catg() const
    {
        if (val < static_cast<float>(18.5))
        {
            return "Underweight";
        }
        else if (val < static_cast<float>(25.0))
        {
            return "Normal Weight";
        }
        else if (val < static_cast<float>(30.0))
        {
            return "Overweight";
        }
        else
        {
            return "Obese";
        }
    }

    friend ostream& operator<<(ostream& os, const BMI& bmi)
    {
        os << "BMI: " << fixed << setprecision(1) << bmi.val << " (" << bmi.catg() << ")";

        return os;
    }
};

void greet() 
{
    cout << "Welcome to the Calorie Burned Calculator!\n";
    cout << "Created by Nick Luca\n";
    cout << "This program calculates the calories burned based on your workouts duration and intensity!\n\n";
}

int main() 
{
    greet();

    User user;
    WorkoutLog log;
    CalorieCalculator calculator;

    float w, h;

    cout << "Enter your weight (kg): ";
    while (!(cin >> w) || w <= 0)
    {
        cout << "Invalid input please enter a positive weight in kg: ";
        cin.clear();
        cin.ignore(1000, '\n');

    }

    cout << "Enter your height (cm): ";
    while (!(cin >> h) || h <= 0)
    {
        cout << "Invalid input please enter a positive height in cm: ";
        cin.clear();
        cin.ignore(1000, '\n');
    }

    user = User(w, h);

    BMI bmi(user);
    cout << "\n" << bmi << "\n\n";

    int numOfWorkouts;
    cout << "How many workouts did you do today? ";

    while (!(cin >> numOfWorkouts) || numOfWorkouts <= 0)
    {
        cout << "Invalid input please enter a positive number: ";
        cin.clear();
        cin.ignore(1000, '\n');
    }

    for (int i = 0; i < numOfWorkouts; i++)
    {
        int mins;
        float intensity;

        cout << "\nWorkout " << i + 1 << ":\n";

        cout << "Enter duration (mins): ";
        while (!(cin >> mins) || mins <= 0)
        {
            cout << "Invalid input please enter a positive number: ";
            cin.clear();
            cin.ignore(1000, '\n');
        }

        cout << "Enter intensity (1.0 - 3.0): ";
        while (!(cin >> intensity) || intensity < 1.0 || intensity > 3.0)
        {
            cout << "Invalid input please enter a number between 1.0 and 3.0: ";
            cin.clear();
            cin.ignore(1000, '\n');
        }
        log.addWorkout(Workout(mins, intensity));
    }

    log.showTotal(user);

    return 0;
}
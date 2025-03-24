// Author: ChatGPT
// For: Caleb Fowler Nick Luca
// Homework 4, Deliverable 1

#include <iostream>
#include <iomanip>
#include <limits>

using namespace std;

// User Profile Class
class UserProfile {
private:
    float weight;  // in kilograms
    float height;  // in centimeters

public:
    UserProfile(float w = 0, float h = 0) : weight(w), height(h) {}

    // Convert constructor to/from int (weight and height in kg and cm)
    UserProfile(int w, int h) {
        weight = static_cast<float>(w);
        height = static_cast<float>(h);
    }

    // Stream insertion and extraction operators for UserProfile
    friend ostream& operator<<(ostream& os, const UserProfile& profile) {
        os << "Weight: " << profile.weight << " kg, Height: " << profile.height << " cm";
        return os;
    }

    friend istream& operator>>(istream& is, UserProfile& profile) {
        is >> profile.weight >> profile.height;
        return is;
    }

    // Getter functions
    float getWeight() const { return weight; }
    float getHeight() const { return height; }
};

// Workout Class
class Workout {
private:
    int minutes;  // workout duration in minutes
    float intensity; // workout intensity (1.0 - 3.0)

public:
    Workout(int min = 0, float inten = 1.0) : minutes(min), intensity(inten) {}

    // Convert constructor to/from int (minutes)
    Workout(int min) : minutes(min), intensity(1.0) {}

    // Stream insertion and extraction operators for Workout
    friend ostream& operator<<(ostream& os, const Workout& workout) {
        os << "Duration: " << workout.minutes << " min, Intensity: " << workout.intensity;
        return os;
    }

    friend istream& operator>>(istream& is, Workout& workout) {
        is >> workout.minutes >> workout.intensity;
        return is;
    }

    // Getter functions
    int getMinutes() const { return minutes; }
    float getIntensity() const { return intensity; }
};

// CalorieCalculator Functor
class CalorieCalculator {
public:
    float operator()(const UserProfile& profile, const Workout& workout) {
        // Simple calorie calculation (calories burned per minute)
        float caloriesBurned = workout.getMinutes() * workout.getIntensity() * 0.07 * profile.getWeight();
        return caloriesBurned;
    }
};

// Workout Log Class for Dynamic Memory Management
class WorkoutLog {
private:
    Workout* workouts;
    int size;
    int capacity;

    void resize(int newCapacity) {
        Workout* newWorkouts = new Workout[newCapacity];
        for (int i = 0; i < size; ++i) {
            newWorkouts[i] = workouts[i];
        }
        delete[] workouts;
        workouts = newWorkouts;
        capacity = newCapacity;
    }

public:
    WorkoutLog(int cap = 5) : size(0), capacity(cap) {
        workouts = new Workout[capacity];
    }

    ~WorkoutLog() {
        delete[] workouts;
    }

    void addWorkout(const Workout& workout) {
        if (size == capacity) {
            resize(capacity * 2); // double capacity if needed
        }
        workouts[size++] = workout;
    }

    void displaySummary() const {
        cout << "+---------------------------------+" << endl;
        cout << "| No | Duration | Intensity | Calories Burned |" << endl;
        cout << "+---------------------------------+" << endl;
        CalorieCalculator calc;
        for (int i = 0; i < size; ++i) {
            float calories = calc(UserProfile(70, 175), workouts[i]);  // Example weight and height
            cout << "| " << setw(2) << i + 1 << " | " << setw(8) << workouts[i].getMinutes()
                << " | " << setw(9) << workouts[i].getIntensity() << " | " << setw(14) << calories << " |" << endl;
        }
        cout << "+---------------------------------+" << endl;
    }
};

// Program Greeting and Initialization
void greet() {
    cout << "Welcome to the Fitness Calculator!" << endl;
    cout << "Created by Nick Luca." << endl;
    cout << "This program calculates the calories burned based on your workouts." << endl;
}

int main() {
    greet();

    UserProfile userProfile;
    WorkoutLog log;
    CalorieCalculator calculator;

    // Input user profile (weight, height)
    cout << "Enter your weight (kg) and height (cm): ";
    while (!(cin >> userProfile)) {
        cout << "Invalid input! Please enter valid weight and height: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    // Input workouts
    int numWorkouts;
    cout << "How many workouts did you do today? ";
    while (!(cin >> numWorkouts) || numWorkouts <= 0) {
        cout << "Invalid number of workouts! Please enter a positive number: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    for (int i = 0; i < numWorkouts; ++i) {
        int minutes;
        float intensity;
        cout << "Enter the duration (in minutes) and intensity (1.0 - 3.0) for workout " << i + 1 << ": ";
        while (!(cin >> minutes >> intensity) || minutes <= 0 || intensity < 1.0 || intensity > 3.0) {
            cout << "Invalid input! Please enter valid workout duration and intensity (1.0 - 3.0): ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        log.addWorkout(Workout(minutes, intensity));
    }

    // Display workout log summary
    log.displaySummary();

    return 0;
}
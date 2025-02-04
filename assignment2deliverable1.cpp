// Author: ChatGPT
// For: Caleb Fowler Nick Luca
// Homework 2, Deliverable 1

#include <iostream>
#include <iomanip>
#include <cassert>

using namespace std;

// Struct for storing incident details
struct IncidentReport {
    int timestamp;
    int severity;
    double resolutionTime;

    IncidentReport(int t, int s, double r) : timestamp(t), severity(s), resolutionTime(r) {}

    double computeRiskLevel() const {
        return severity * (resolutionTime > 0 ? 1.0 / resolutionTime : 1.0);
    }
};

// Class representing an affected system
class AffectedSystem {
public:
    string systemName;
    bool resolved;

    AffectedSystem(string name) : systemName(name), resolved(false) {}

    void markResolved() {
        resolved = true;
    }
};

// Class representing a security incident
class Incident {
public:
    IncidentReport report;
    AffectedSystem** affectedSystems;
    int systemCount;

    Incident(int timestamp, int severity, double resolutionTime, int maxSystems)
        : report(timestamp, severity, resolutionTime), systemCount(0) {
        assert(severity >= 1 && severity <= 10);
        assert(resolutionTime > 0);
        affectedSystems = new AffectedSystem * [maxSystems];
    }

    ~Incident() {
        for (int i = 0; i < systemCount; i++) {
            delete affectedSystems[i];
        }
        delete[] affectedSystems;
    }

    void addSystem(string systemName) {
        affectedSystems[systemCount++] = new AffectedSystem(systemName);
    }

    void display() const {
        cout << "| " << setw(10) << report.timestamp << " | " << setw(8) << report.severity
            << " | " << setw(14) << report.resolutionTime << " | " << setw(12)
            << (report.computeRiskLevel() > 5 ? "HIGH" : "LOW") << " |" << endl;
    }
};

// Class representing a company tracking incidents
class Company {
public:
    string name;
    Incident** incidents;
    int incidentCount;
    int capacity;

    Company(string cname, int cap) : name(cname), incidentCount(0), capacity(cap) {
        incidents = new Incident * [capacity];
    }

    ~Company() {
        for (int i = 0; i < incidentCount; i++) {
            delete incidents[i];
        }
        delete[] incidents;
    }

    void addIncident(int timestamp, int severity, double resolutionTime) {
        if (incidentCount == capacity) {
            resize();
        }
        incidents[incidentCount++] = new Incident(timestamp, severity, resolutionTime, 5);
    }

    void resize() {
        int newCapacity = capacity * 2;
        Incident** newArr = new Incident * [newCapacity];
        for (int i = 0; i < incidentCount; i++) {
            newArr[i] = incidents[i];
        }
        delete[] incidents;
        incidents = newArr;
        capacity = newCapacity;
    }

    void displayIncidents() const {
        cout << "\n| Timestamp | Severity | Resolution Time | Risk Level  |\n";
        cout << "--------------------------------------------------\n";
        for (int i = 0; i < incidentCount; i++) {
            incidents[i]->display();
        }
    }
};

int main() {
    // Greeting Section
    cout << "Cybersecurity Breach Tracker" << endl;
    cout << "Developed by: Nick Luca" << endl;
    cout << "--------------------------------" << endl;

    Company company("TechSecure Ltd.", 2);

    int timestamp, severity;
    double resolutionTime;

    cout << "Enter incident timestamp(Must be a number): ";
    cin >> timestamp;

    do {
        cout << "Enter severity level (1-10): ";
        cin >> severity;
    } while (severity < 1 || severity > 10);

    do {
        cout << "Enter resolution time (positive value): ";
        cin >> resolutionTime;
    } while (resolutionTime <= 0);

    company.addIncident(timestamp, severity, resolutionTime);
    company.displayIncidents();

    return 0;
}

// Author: Caleb Fowler Nick Luca
// Improvements to ChatGPT
// Homework 2, Deliverable 2

#include <iostream>
#include <cassert>
#include <iomanip>
#include <string>

using namespace std;

struct IncidentReport
{
	int timestamp, danger;
	double resolvedTime;
	string periodTime;

	IncidentReport(int t, const string& p, int d, double r) : timestamp(t), periodTime(p), danger(d), resolvedTime(r) {}

	double calculateRiskLevel() const
	{
		if (resolvedTime > 0)
		{
			return danger * (1.0 / (resolvedTime + 0.01));
		}
		else
		{
			return danger * 1.0;
		}
	}
};

class AffectedSystems
{
public:
	string systemName;
	bool resolved;

	AffectedSystems(const string& name) : systemName(name), resolved(false) {}

	void checkResolved()
	{
		resolved = true;
	}
};

class Incident
{
public:
	IncidentReport report;
	AffectedSystems** affectedSystems;
	int systemCount, systemMax;

	Incident(int timestamp, const string& periodTime, int danger, double resolvedTime, int systemMax)
		: report(timestamp, periodTime, danger, resolvedTime), systemCount(0), systemMax(systemMax)
	{
		assert(danger >= 1 && danger <= 10);
		assert(resolvedTime >= 0);
		assert(systemMax > 0);
		affectedSystems = new AffectedSystems*[systemMax];
	}

	~Incident()
	{
		for (int i = 0; i < systemCount; i++)
		{
			delete affectedSystems[i];
		}
		delete[] affectedSystems;
		affectedSystems = nullptr;
	}

	void addSystem(const string& systemName)
	{
		assert(systemCount < systemMax);

		affectedSystems[systemCount] = new AffectedSystems(systemName);
		systemCount++;
	}

	void displayReports() const
	{
		string riskLvl;
		if (report.calculateRiskLevel() > 5)
		{
			riskLvl = "HIGH";
		}
		else
		{
			riskLvl = "LOW";
		}

		cout << "| " << setw(10) << left << report.timestamp << setw(4) << report.periodTime << " | " << setw(12) << right << report.danger
			<< " | " << setw(16) << right << report.resolvedTime
			<< " | " << setw(10) << left << riskLvl << " |\n";
	}
};

class Company
{
public:
	string name;
	Incident** incidents;
	int incidentCount, amount;

	Company(const string& cname, int amt) : name(cname), incidentCount(0), amount(amt)
	{
		incidents = new Incident * [amount];
	}

	~Company()
	{
		for (int i = 0; i < incidentCount; i++)
		{
			delete incidents[i];
		}
		delete[] incidents;
		incidents = nullptr;
	}

	void addIncident(int timestamp, const string& periodTime, int danger, double resolvedTime)
	{
		if (incidentCount >= amount)
		{
			resize();
		}
		incidents[incidentCount] = new Incident(timestamp, periodTime, danger, resolvedTime, 5);
		incidentCount++;
	}

	void resize()
	{
		int newAmount = (amount <= 0) ? 1 : amount * 2;
		Incident** newArray = new Incident * [newAmount];

		for (int i = 0; i < incidentCount; i++)
		{
			newArray[i] = incidents[i];
		}

		delete[] incidents;
		incidents = newArray;
		amount = newAmount;
	}

	void displayIncidents() const
	{
		if (incidentCount == 0)
		{
			cout << "Nothing on record\n\n";
			return;
		}
		
		cout << "\n| " << setw(10) << left << "Time" << setw(4) << "AM/PM" << " | " << setw(12) << right << "Danger Level" << " | " << setw(16) << right << "Resolution Time"
			<< " | " << setw(10) << left << "Risk Level" << " |\n";
		cout << "---------------------------------------------------------------\n";
		
		for (int i = 0; i < incidentCount; i++)
		{
			incidents[i]->displayReports();
		}
	}
};

void menu(Company& company)
{
	int userChoice;

	do
	{
		cout << "1. Enter a new attack\n";
		cout << "2. View incident records\n";
		cout << "3. Exit\n\n";
		cout << "Enter your choice: ";
		cin >> userChoice;

		while (cin.fail() || userChoice < 1 || userChoice > 3)
		{
			cin.clear();
			cin.ignore(1000, '\n');
			cout << '\n';
			cout << "Invalid input!\n";
			cout << "Enter a number between 1 and 3: ";
			cin >> userChoice;
			cout << '\n';
		}

		if (userChoice == 1)
		{
			int timestamp, danger;
			double resolvedTime;
			string periodTime;

			cout << "Enter the time of the attack (1-12): ";
			while (!(cin >> timestamp) || timestamp < 1 || timestamp > 12)
			{
				cin.clear();
				cin.ignore(1000, '\n');
				cout << '\n';
				cout << "Invalid input!\n";
				cout << "Enter a number between 1 and 12: ";
				cin >> timestamp;
				cout << '\n';
			}

			cout << "AM or PM: ";
			cin.ignore(1000, '\n');
			getline(cin, periodTime);
			periodTime[0] = static_cast<char>(toupper(periodTime[0]));
			periodTime[1] = static_cast<char>(toupper(periodTime[1]));
			while (periodTime != "AM" && periodTime != "PM")
			{
				cout << "Invalid input! Enter AM or PM: ";
				getline(cin, periodTime);
				for (char& c : periodTime) c = toupper(c);
			}

			cout << "Enter the danger level (1-10): ";
			while (!(cin >> danger) || danger < 1 || danger > 10)
			{
				cin.clear();
				cin.ignore(1000, '\n');
				cout << '\n';
				cout << "Invalid input!\n";
				cout << "Enter a number between 1 and 10: ";
				cin >> danger;
				cout << '\n';
			}

			cout << "Enter the resolution time (>= 0): ";
			while (!(cin >> resolvedTime) || resolvedTime < 0)
			{
				cin.clear();
				cin.ignore(1000, '\n');
				cout << '\n';
				cout << "Invalid input!\n";
				cout << "Enter a number (>= 0): ";
				cin >> resolvedTime;
				cout << '\n';
			}

			company.addIncident(timestamp, periodTime, danger, resolvedTime);
			cout << "\nIncident record added!\n\n";
		}
		else if (userChoice == 2)
		{
			company.displayIncidents();
		}
	} while (userChoice != 3);
}

int main()
{
	cout << "System Breach Tracker\n";
	cout << "Created by: Nick Luca (and ChatGPT)\n";
	cout << "-------------------------------------------\n";

	Company company("TechSomething Ltd.", 2);

	menu(company);

	return 0;
}
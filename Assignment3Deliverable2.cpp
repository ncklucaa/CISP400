// Author: Caleb Fowler Nick Luca
// Improvements to ChatGPT
// Homework 3, Deliverable 2

#include <iostream>
#include <cassert>
#include <cstring>
#include <iomanip>
#include <string>

using namespace std;

void setWebsite(const string& site);
void setUser(const string& user);
void setPass(const string& pass);
void resizeArr();
void addCreds(const string& site, const string& user, const string& pass);
void showCreds(bool showPw = false);

struct pwPolicy
{
	int min, max;
};

struct Owner
{
	string owner;
};

class Credentials
{
private:
	string website, username, password;

public:
	Credentials(const string& site, const string& user, const string& pass)
	{
		website = site;
		username = user;
		password = pass;
	}

	~Credentials() {}

	const string& getWebsite() const
	{
		return website;
	}

	const string& getUser() const
	{
		return username;
	}

	const string& getPass() const
	{
		return password;
	}

	void setWebsite(const string& site)
	{
		website = site;
	}

	void setUser(const string& user)
	{
		username = user;
	}

	void setPass(const string& pass)
	{
		password = pass;
	}
};

ostream& operator<<(ostream& os, const Credentials& creds)
{
	os << left << setw(15) << creds.getWebsite() << " | " << setw(15) << creds.getUser() << " | " << "[PROTECTED]\n";

	return os;
}

istream& operator>>(istream& is, Credentials& creds)
{
	string site, user, pass;

	cout << "Enter website: ";
	getline(is, site);

	cout << "Enter username: ";
	getline(is, user);

	cout << "\n";
	cout << "Password Requirements\n";
	cout << "Minimum 8 characters\n";
	cout << "Maximum 20 characters\n";
	cout << "No spaces\n\n";

	do
	{
		cout << "Enter password: ";
		getline(is, pass);

		if (pass.length() < 8)
		{
			cout << "Invalid password must be at least 8 characters\n";
		}
	} while (pass.length() < 8);

	creds.setWebsite(site);
	creds.setUser(user);
	creds.setPass(pass);

	return is;
}

class Accounts
{
private:
	pwPolicy policy = { 8, 20 };
	Credentials** credentials;
	int size, cap;

	void resizeArr()
	{
		int newCap = cap * 2;
		Credentials** temp = new Credentials * [newCap];

		for (int i = 0; i < size; i++)
		{
			temp[i] = credentials[i];
		}
		delete[] credentials;
		credentials = temp;
		cap = newCap;
	}

public:
	Accounts() : size(0), cap(2) 
	{
		credentials = new Credentials * [cap];
	}

	~Accounts()
	{
		for (int i = 0; i < size; i++)
		{
			delete credentials[i];
		}
		delete[] credentials;
	}

	void addCreds(const string& site, const string& user, const string& pass)
	{
		assert(pass.length() >= policy.min && pass.length() <= policy.max && "Password must be following the requirements");

		if (size == cap)
		{
			resizeArr();
		}
		credentials[size++] = new Credentials(site, user, pass);
	}

	void showCreds(bool showPw = false)
	{
		cout << "\nStored Credentials:\n";
		cout << "-------------------------------------------------------\n";
		cout << "| Website         | Username        | Password        |\n";
		cout << "-------------------------------------------------------\n";

		for (int i = 0; i < size; i++)
		{
			cout << "| " << setw(15) << credentials[i]->getWebsite() << " | " << setw(15) << credentials[i]->getUser() << " | ";

			if (showPw)
			{
				cout << credentials[i]->getPass();
			}
			else
			{
				cout << "[PROTECTED]";
			}
			cout << " | \n";
		}
		cout << "-------------------------------------------------------\n";
	}
};

int main()
{
	cout << "=============================\n";
	cout << "  Password Vault Manager\n";
	cout << "  Developed by Nick Luca\n";
	cout << "=============================\n";

	cout << '\n';
	Owner owner;
	cout << "Enter your name: ";
	getline(cin, owner.owner);

	Accounts user;
	int numOfCreds;

	cout << "How many credentials would you like to enter?: ";
	while (!(cin >> numOfCreds) || numOfCreds <= 0)
	{
		cout << "Enter a positive number: ";
		cin.clear();
		cin.ignore(1000, '\n');
	}
	cin.ignore(1000, '\n');

	for (int i = 0; i < numOfCreds; i++)
	{
		cout << "\nAdding Credential " << i + 1 << ":\n";
		Credentials temp("", "", "");
		cin >> temp;
		user.addCreds(temp.getWebsite(), temp.getUser(), temp.getPass());
	}

	int userChoice;

	do
	{
		cout << "\n1. View credentials\n";
		cout << "2. Add more credentials\n";
		cout << "3. Exit\n\n";
		cout << "Enter your choice: ";

		while (!(cin >> userChoice) || userChoice < 1 || userChoice > 3)
		{
			cout << "Enter a number between 1 and 3: ";
			cin.clear();
			cin.ignore(1000, '\n');
		}
		cin.ignore(1000, '\n');

		if (userChoice == 1)
		{
			char show;
			do
			{
				cout << "Show passwords? (y/n): ";
				cin >> show;
				show = tolower(show);
			} while (show != 'y' && show != 'n');

			user.showCreds(show == 'y');
		}
		else if (userChoice == 2)
		{
			int addCreds2;
			cout << "How many credentials would you like to add?: ";

			while (!(cin >> addCreds2) || addCreds2 <= 0)
			{
				cout << "Enter a positive number\n\n";
				cout << "How many credentials would you like to add?: ";
				cin.clear();
				cin.ignore(1000, '\n');
			}
			cin.ignore(1000, '\n');

			for (int i = 0; i < addCreds2; i++)
			{
				cout << "\nAdding Credential " << i + 1 << ":\n";
				Credentials temp("", "", "");
				cin >> temp;
				user.addCreds(temp.getWebsite(), temp.getUser(), temp.getPass());
			}
		}
	} while (userChoice != 3);

	cout << "Exiting\n";
	cout << "Goodbye " << owner.owner << "!";
	
	return 0;
}
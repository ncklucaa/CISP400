// Author: ChatGPT
// For: Caleb Fowler Nick Luca
// Homework 3, Deliverable 1

#include <iostream>
#include <iomanip>
#include <cassert>
#include <cstring>

using namespace std;

// Struct for password policy
struct PasswordPolicy {
    int minLength;
    int maxLength;
    bool requiresSpecialChar;
};

// Class representing a credential entry
class Credential {
private:
    string website;
    string username;
    string password;

public:
    Credential(const string& site, const string& user, const string& pass) {
        website = site;
        username = user;
        password = pass;
    }

    ~Credential() {}

    // Getters
    const string& getWebsite() const { return website; }
    const string& getUsername() const { return username; }

    // Setters
    void setWebsite(const string& site) {
        website = site;
    }

    void setUsername(const string& user) {
        username = user;
    }

    void setPassword(const string& pass) {
        password = pass;
    }
};

// Overloading stream operators
ostream& operator<<(ostream& os, const Credential& cred) {
    os << left << setw(15) << cred.getWebsite() << " | "
        << setw(15) << cred.getUsername() << " | "
        << "[PROTECTED]";
    return os;
}

istream& operator>>(istream& is, Credential& cred) {
    char site[50], user[50], pass[50];
    cout << "Enter website: "; is >> site;
    cout << "Enter username: "; is >> user;
    cout << "Enter password: "; is >> pass;

    cred.setWebsite(site);
    cred.setUsername(user);
    cred.setPassword(pass);
    return is;
}

// User Account managing multiple credentials
class UserAccount {
private:
    PasswordPolicy policy = { 8, 20, true }; // Enforce password length
    Credential** credentials;
    int size;
    int capacity;

    void resizeArray() {
        int newCapacity = capacity * 2;
        Credential** temp = new Credential * [newCapacity];
        for (int i = 0; i < size; i++) {
            temp[i] = credentials[i];
        }
        delete[] credentials;
        credentials = temp;
        capacity = newCapacity;
    }

public:
    UserAccount() : size(0), capacity(2) {
        credentials = new Credential * [capacity];
    }

    ~UserAccount() {
        for (int i = 0; i < size; i++) {
            delete credentials[i];
        }
        delete[] credentials;
    }

    void addCredential(const string& site, const string& user, const string& pass) {
        assert(pass.length() >= policy.minLength && pass.length() <= policy.maxLength &&
            "Password must follow the length policy!");

        if (size == capacity) {
            resizeArray();
        }
        credentials[size++] = new Credential(site, user, pass);
    }

    void displayCredentials() {
        cout << "\nStored Credentials:" << endl;
        cout << left << setw(15) << "Website" << " | "
            << setw(15) << "Username" << " | "
            << "Password" << endl;
        cout << string(50, '-') << endl;
        for (int i = 0; i < size; i++) {
            cout << left << setw(15) << credentials[i]->getWebsite() << " | "
                << setw(15) << credentials[i]->getUsername() << " | "
                << "[PROTECTED]" << endl;
        }
    }
};

int main() {
    cout << "=============================" << endl;
    cout << "  Password Vault Manager" << endl;
    cout << "  Developed by Nick Luca" << endl;
    cout << "=============================" << endl;

    UserAccount user;
    char site[50], userName[50], pass[50];

    for (int i = 0; i < 3; i++) {
        cout << "\nAdding Credential " << i + 1 << ":" << endl;
        cout << "Enter website: "; cin >> site;
        cout << "Enter username: "; cin >> userName;

        do {
            cout << "Enter password (min 8 chars): "; cin >> pass;
            if (strlen(pass) < 8) {
                cout << "Error: Password must be at least 8 characters!\n";
            }
        } while (strlen(pass) < 8);

        user.addCredential(site, userName, pass);
    }

    user.displayCredentials();
    return 0;
}

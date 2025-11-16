#include <bits/stdc++.h>
using namespace std;

class PasswordManager {
private:
    string username;
    string masterPassword;

    string usersFile = "users.txt";           // Stores registered users
    string passwordsFilePrefix = "vault_";    // Each user has their own vault file

public:
    void registerUser();
    bool loginUser();
    void userMenu(string username);
    void addPassword(string username);
    void viewPasswords(string username);
    void deletePassword(string username);
};

void PasswordManager::registerUser() {
    cout << "\n=== Register New User ===\n";
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter master password: ";
    cin >> masterPassword;

    ofstream out(usersFile, ios::app);
    out << username << " " << masterPassword << endl;
    out.close();

    cout << "✅ User registered successfully!\n";
}

bool PasswordManager::loginUser() {
    cout << "\n=== Login ===\n";
    cout << "Username: ";
    cin >> username;
    cout << "Password: ";
    cin >> masterPassword;

    ifstream in(usersFile);
    string user, pass;
    bool found = false;
    while (in >> user >> pass) {
        if (user == username && pass == masterPassword) {
            found = true;
            break;
        }
    }
    in.close();

    if (found) {
        cout << "✅ Login successful!\n";
        userMenu(username);
        return true;
    } else {
        cout << "❌ Invalid credentials!\n";
        return false;
    }
}

void PasswordManager::userMenu(string username) {
    int choice;
    do {
        cout << "\n=== Password Vault for " << username << " ===\n";
        cout << "1. Add New Password\n";
        cout << "2. View Saved Passwords\n";
        cout << "3. Delete a Password\n";
        cout << "4. Logout\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1: addPassword(username); break;
        case 2: viewPasswords(username); break;
        case 3: deletePassword(username); break;
        case 4: cout << "Logging out...\n"; break;
        default: cout << "Invalid choice!\n";
        }
    } while (choice != 4);
}

void PasswordManager::addPassword(string username) {
    string site, userId, password;
    cout << "\nEnter site/app name: ";
    cin >> site;
    cout << "Enter user ID/email: ";
    cin >> userId;
    cout << "Enter password: ";
    cin >> password;

    string fileName = passwordsFilePrefix + username + ".txt";
    ofstream out(fileName, ios::app);
    out << site << " " << userId << " " << password << endl;
    out.close();

    cout << "✅ Password saved successfully!\n";
}

void PasswordManager::viewPasswords(string username) {
    string fileName = passwordsFilePrefix + username + ".txt";
    ifstream in(fileName);
    if (!in) {
        cout << "❌ No saved passwords yet.\n";
        return;
    }

    cout << "\n=== Saved Passwords ===\n";
    string site, userId, password;
    int count = 0;
    while (in >> site >> userId >> password) {
        cout << ++count << ". " << site << " | " << userId << " | " << password << endl;
    }
    if (count == 0) cout << "No passwords found.\n";
    in.close();
}

void PasswordManager::deletePassword(string username) {
    string fileName = passwordsFilePrefix + username + ".txt";
    ifstream in(fileName);
    if (!in) {
        cout << "❌ No saved passwords yet.\n";
        return;
    }

    vector<tuple<string, string, string>> entries;
    string site, userId, password;
    while (in >> site >> userId >> password) {
        entries.push_back({site, userId, password});
    }
    in.close();

    cout << "\n=== Delete Password ===\n";
    for (int i = 0; i < entries.size(); i++) {
        cout << i + 1 << ". " << get<0>(entries[i]) << " | " << get<1>(entries[i]) << " | " << get<2>(entries[i]) << endl;
    }

    cout << "Enter number to delete: ";
    int num;
    cin >> num;

    if (num < 1 || num > entries.size()) {
        cout << "❌ Invalid number!\n";
        return;
    }

    ofstream out(fileName);
    for (int i = 0; i < entries.size(); i++) {
        if (i != num - 1)
            out << get<0>(entries[i]) << " " << get<1>(entries[i]) << " " << get<2>(entries[i]) << endl;
    }
    out.close();

    cout << "✅ Entry deleted successfully!\n";
}

int main() {
    PasswordManager pm;
    int choice;

    do {
        cout << "\n====== PASSWORD MANAGEMENT SYSTEM ======\n";
        cout << "1. Register\n";
        cout << "2. Login\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: pm.registerUser(); break;
        case 2: pm.loginUser(); break;
        case 3: cout << "Exiting program...\n"; break;
        default: cout << "Invalid choice!\n";
        }
    } while (choice != 3);

    return 0;
}

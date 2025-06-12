#include "precompiler.h"

int getNextUserID() {
    std::ifstream infile("users.txt");
    int lastID = 0;
    std::string line;
    while (std::getline(infile, line)) {
        std::istringstream iss(line);
        int id;
        std::string u, p;
        if (iss >> id >> u >> p) {
            lastID = id;
        }
    }
    return lastID + 1;
}

void registerUser() {
    std::string username, password;

    std::cin.ignore();
    std::cout << "Enter a username: ";
    std::getline(std::cin, username);
    std::cout << "Enter a password: ";
    std::getline(std::cin, password);

    int newID = getNextUserID();

    std::ofstream outfile("users.txt", std::ios::app);
    outfile << newID << " " << username << " " << password << "\n";

    std::cout << "Registration successful! Your user ID is: " << newID << "\n";
}

void loginUser() {
    std::string username, password;
    std::cin.ignore();
    std::cout << "Username: ";
    std::getline(std::cin, username);
    std::cout << "Password: ";
    std::getline(std::cin, password);

    std::ifstream infile("users.txt");
    std::string line;
    while (std::getline(infile, line)) {
        std::istringstream iss(line);
        int id;
        std::string u, p;
        if (iss >> id >> u >> p) {
            if (u == username && p == password) {
                isLoggedIn = true;
                currentUser.id = id;
                currentUser.username = u;
                currentUser.password = p;
                std::cout << "Login successful! Welcome, " << currentUser.username << " (ID: " << currentUser.id << ").\n";
                return;
            }
        }
    }

    std::cout << "Login failed! Invalid username or password.\n";
}

void showAuthMenu() {
    int choice;
    while (!isLoggedIn) {
        std::cout << "\n--- User Authentication ---\n";
        std::cout << "1. Register\n";
        std::cout << "2. Login\n";
        std::cout << "0. Exit\n";
        std::cout << "Choice: ";
        std::cin >> choice;

        switch (choice) {
        case 1: registerUser(); break;
        case 2: loginUser(); break;
        case 0: exit(0);
        default: std::cout << "Invalid choice!\n"; break;
        }
    }
}
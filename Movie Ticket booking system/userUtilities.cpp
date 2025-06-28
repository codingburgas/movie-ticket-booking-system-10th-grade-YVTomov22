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
    User newUser;
    std::cin.ignore();

    std::cout << "Enter username: ";
    std::getline(std::cin, newUser.username);
    std::cout << "Enter password: ";
    std::getline(std::cin, newUser.password);

    // Ask for role
    std::cout << "Register as (admin/user): ";
    std::getline(std::cin, newUser.role);

    while (newUser.role != "admin" && newUser.role != "user") {
        std::cout << "Invalid role. Enter 'admin' or 'user': ";
        std::getline(std::cin, newUser.role);
    }

    newUser.id = getNextUserID();

    std::ofstream outFile("users.txt", std::ios::app);
    outFile << newUser.id << "," << newUser.username << "," << newUser.password << "," << newUser.role << "\n";
    outFile.close();

    std::cout << "Registration successful. Your ID is " << newUser.id << "\n";
}


void loginUser() {
    std::string username, password;
    std::cin.ignore();
    std::cout << "Enter username: ";
    std::getline(std::cin, username);
    std::cout << "Enter password: ";
    std::getline(std::cin, password);

    std::ifstream inFile("users.txt");
    std::string line;
    bool found = false;

    while (std::getline(inFile, line)) {
        std::istringstream iss(line);
        std::string idStr, uname, pass, role;
        std::getline(iss, idStr, ',');
        std::getline(iss, uname, ',');
        std::getline(iss, pass, ',');
        std::getline(iss, role);

        if (uname == username && pass == password) {
            currentUser.id = std::stoi(idStr);
            currentUser.username = uname;
            currentUser.password = pass;
            currentUser.role = role;

            isLoggedIn = true;
            std::cout << "Login successful as " << role << "!\n";
            found = true;
            break;
        }
    }

    if (!found) {
        std::cout << "Invalid username or password.\n";
    }
}




void showAuthMenu() {
    while (!isLoggedIn) {
        int choice;
        std::cout << "\n--- Welcome ---\n";
        std::cout << "1. Register\n";
        std::cout << "2. Login\n";
        std::cout << "0. Exit\n";
        std::cout << "Choose an option: ";
        std::cin >> choice;

        switch (choice) {
        case 1:
            registerUser();
            break;
        case 2:
            loginUser();
            break;
        case 0:
            gameOn = false;
        default:
            std::cout << "Invalid choice.\n";
        }
    }
}
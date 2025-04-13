#include "precompiler.h"

void showMenu() {
    std::cout << "Welcome to the Movie Ticket Booking System\n";
    std::cout << "-----------------------------------------------\n";
    std::cout << "1. View all movies\n";
    std::cout << "2. Search for a movie\n";
    std::cout << "3. Book a ticket\n";
    std::cout << "4. Admin panel\n";
    std::cout << "5. Exit\n";
    std::cout << "Please choose an option: ";
}

void handleChoice(int choice) {
    
    switch (choice) {
    case 1:
        std::cout << "Showing all movies...\n";
        // TODO: Display movie list
        break;
    case 2:
        std::cout << "Searching for a movie...\n";
        // TODO: Add search logic
        break;
    case 3:
        std::cout << "Booking a ticket...\n";
        // TODO: Add booking logic
        break;
    case 4:
        std::cout << "Admin panel accessed...\n";
        // TODO: Admin actions (add/update/delete)
        break;
    case 5:
        std::cout << "Goodbye!\n";
        gameOn = false;
        break;
    default:
        std::cout << "Invalid choice. Try again.\n";
    }
}
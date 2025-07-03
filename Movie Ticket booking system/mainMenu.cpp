#include "precompiler.h"

void showMenu() {
    int choice;
    std::cout << "\n- Movie Ticket Booking System -\n";
    std::cout << "1. List All Cinemas and Halls\n";
    std::cout << "2. View All Showtimes of a Movie\n";
    std::cout << "3. Search Movie\n";
    std::cout << "4. Select Seat\n";

    // Only show these options if the user is an admin
    if (currentUser.role == "admin") {
        std::cout << "---------------------------------\n";
        std::cout << "Admin Panel:\n";
        std::cout << "5. Add Movie\n";
        std::cout << "6. Add Cinema\n";
        std::cout << "7. Delete Movie\n";
        std::cout << "8. Delete Cinema\n";
        std::cout << "9. View Cinema Reservations\n";
        std::cout << "---------------------------------\n";
    }

    std::cout << "0. Exit\n";
    std::cout << "Choose an option: ";
    std::cin >> choice;

    if (std::cin.fail()) {
        std::cout << "Invalid input! Please enter a number.\n";
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        return;
    }

    switch (choice) {
    case 1:
        system("cls");
        listCinemasAndHalls();
        break;
    case 2:
        system("cls");
        listShowtimes();
        break;
    case 3:
        system("cls");
        searchMovies();
        break;
    case 4:
        system("cls");
        seatSelector();
        break;
    case 5:
        if (currentUser.role == "admin") {
            system("cls");
            addMovie();
        }
        else {
            std::cout << "Invalid choice!\n";
        }
        break;
    case 6:
        if (currentUser.role == "admin") {
            system("cls");
            addCinema();
        }
        else {
            std::cout << "Invalid choice!\n";
        }
        break;
    case 7:
        if (currentUser.role == "admin") {
            system("cls");
            deleteMovie();
        }
        else {
            std::cout << "Invalid choice!\n";
        }
        break;
    case 8:
        if (currentUser.role == "admin") {
            system("cls");
            deleteCinema();
        }
        else {
            std::cout << "Invalid choice!\n";
        }
        break;
    case 9:
        if (currentUser.role == "admin") {
            system("cls");
            viewCinemaReservations();
        }
        else {
            std::cout << "Invalid choice!\n";
        }
        break;
    case 0:
        gameOn = false;
        system("cls");
        std::cout << "Exiting system. Goodbye!\n";
        break;
    default:
        std::cout << "Invalid choice! Please try again.\n";
        break;
    }
}
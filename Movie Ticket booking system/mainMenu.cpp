#include "precompiler.h"

void showMenu() {
    int choice;
    std::cout << "\n--- Movie Ticket Booking System ---\n";
    std::cout << "1. List All Cinemas and Halls\n";
    std::cout << "2. View All Showtimes of a Movie\n";
    std::cout << "3. Search Movie\n";
    std::cout << "5. Add Movie\n";
    std::cout << "0. Exit\n";
    std::cout << "Choose an option: ";
    std::cin >> choice;

    switch (choice) {
    case 1:
        listCinemasAndHalls();
        break;
    case 2:
        listShowtimes();
        break;
    case 3:
        searchMovies();
        break;
    case 4:
        //seatSelector();
    case 5:
        addMovie();
        break;
    case 6:
        addCinema();
        break;
    case 0:
        gameOn = false;
        system("cls");
        break;
    default:
        std::cout << "Invalid choice!\n";
        break;
    }
}

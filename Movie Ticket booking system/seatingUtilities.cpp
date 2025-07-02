#include "precompiler.h"

void displaySeatingChart(Show& show, int totalSeats) {
    if (show.seats.empty()) {
        int seatsPerRow = 10;
        for (int i = 0; i < totalSeats; ++i) {
            show.seats.emplace_back(i / seatsPerRow + 1, i % seatsPerRow + 1);
        }
    }

    std::cout << "\n--- Seating Arrangement ---\n";
    std::cout << "      Screen This Way\n\n";

    int seatsPerRow = 10;
    for (size_t i = 0; i < show.seats.size(); ++i) {
        if (i % seatsPerRow == 0) {
            if (i != 0) std::cout << "\n";
            std::cout << "Row " << std::setw(2) << show.seats[i].row << ": ";
        }
        int seatNum = show.seats[i].number;
        if (show.seats[i].isBooked) {
            std::cout << "\033[31m" << std::setw(2) << seatNum << " \033[0m";
        }
        else {
            std::cout << "\033[32m" << std::setw(2) << seatNum << " \033[0m";
        }
    }
    std::cout << "\n\nLegend: Green = Available | Red = Booked\n";
}

// All functions below are the final, corrected versions.

// Main function for seat selection process
void seatSelector() {
    if (cinemas.empty()) {
        std::cout << "No cinemas available to select seats from.\n";
        return;
    }

    std::cout << "\nSelect a Cinema:\n";
    for (size_t i = 0; i < cinemas.size(); ++i) {
        std::cout << i + 1 << ". " << cinemas[i].city << "\n";
    }
    int cinemaIndex;
    std::cout << "Choose an option: ";
    std::cin >> cinemaIndex;
    if (std::cin.fail() || cinemaIndex < 1 || cinemaIndex > cinemas.size()) {
        std::cout << "Invalid selection.\n";
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        return;
    }
    Cinema& selectedCinema = cinemas[cinemaIndex - 1];

    if (selectedCinema.halls.empty()) {
        std::cout << "No halls available in this cinema.\n";
        return;
    }
    std::cout << "\nSelect a Hall:\n";
    for (size_t i = 0; i < selectedCinema.halls.size(); ++i) {
        std::cout << i + 1 << ". " << selectedCinema.halls[i].name << "\n";
    }
    int hallIndex;
    std::cout << "Choose an option: ";
    std::cin >> hallIndex;
    if (std::cin.fail() || hallIndex < 1 || hallIndex > selectedCinema.halls.size()) {
        std::cout << "Invalid selection.\n";
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        return;
    }
    Hall& selectedHall = selectedCinema.halls[hallIndex - 1];

    if (selectedHall.movies.empty()) {
        std::cout << "No movies available in this hall.\n";
        return;
    }
    std::cout << "\nSelect a Movie:\n";
    for (size_t i = 0; i < selectedHall.movies.size(); ++i) {
        std::cout << i + 1 << ". " << selectedHall.movies[i].title << "\n";
    }
    int movieIndex;
    std::cout << "Choose an option: ";
    std::cin >> movieIndex;
    if (std::cin.fail() || movieIndex < 1 || movieIndex > selectedHall.movies.size()) {
        std::cout << "Invalid selection.\n";
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        return;
    }
    Movie& selectedMovie = selectedHall.movies[movieIndex - 1];

    if (selectedMovie.shows.empty()) {
        std::cout << "No showtimes available for this movie.\n";
        return;
    }
    std::cout << "\nSelect a Showtime:\n";
    for (size_t i = 0; i < selectedMovie.shows.size(); ++i) {
        std::cout << i + 1 << ". " << selectedMovie.shows[i].time << "\n";
    }
    int showIndex;
    std::cout << "Choose an option: ";
    std::cin >> showIndex;
    if (std::cin.fail() || showIndex < 1 || showIndex > selectedMovie.shows.size()) {
        std::cout << "Invalid selection.\n";
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        return;
    }
    Show& selectedShow = selectedMovie.shows[showIndex - 1];

    system("cls");
    displaySeatingChart(selectedShow, selectedCinema.seat);

    std::vector<int> selectedSeatsThisSession;
    double totalPrice = 0.0;

    while (true) {
        std::cout << "\nEnter row and seat number to book (e.g., 3 5).\n";
        std::cout << "Enter 0 0 to finish selection and proceed to payment: ";
        int row, seatNum;
        std::cin >> row >> seatNum;

        if (std::cin.fail()) {
            std::cout << "Invalid input. Please enter numbers only.\n";
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue;
        }

        if (row == 0 || seatNum == 0) {
            break;
        }

        int seatsPerRow = 10;
        int totalRows = (selectedCinema.seat + seatsPerRow - 1) / seatsPerRow;
        int seatIndex = (row - 1) * seatsPerRow + (seatNum - 1);

        if (row < 1 || row > totalRows || seatNum < 1 || seatNum > seatsPerRow || seatIndex >= selectedCinema.seat) {
            std::cout << "Invalid seat number. Please try again.\n";
            continue;
        }

        if (selectedShow.seats[seatIndex].isBooked) {
            std::cout << "Sorry, that seat is already booked. Please choose another.\n";
        }
        else {
            selectedShow.seats[seatIndex].isBooked = true;
            selectedSeatsThisSession.push_back(seatIndex);

            totalPrice += selectedMovie.price;

            std::cout << "Seat (" << row << ", " << seatNum << ") added! Current Total: $" << std::fixed << std::setprecision(2) << totalPrice << "\n";

            std::cout << "Press Enter to continue...";
            std::cin.ignore(10000, '\n');
            std::cin.get();

            system("cls");
            displaySeatingChart(selectedShow, selectedCinema.seat);
        }
    }

    if (totalPrice > 0) {
        std::cout << "\nYour total is $" << std::fixed << std::setprecision(2) << totalPrice << ".\n";
        std::cout << "1. Confirm and Pay\n";
        std::cout << "2. Cancel Booking\n";
        std::cout << "Choose an option: ";

        int paymentChoice;
        std::cin >> paymentChoice;

        if (paymentChoice == 1) {
            std::cout << "\nPayment successful! Thank you for your booking! Enjoy the show!\n";
        }
        else {
            std::cout << "\nBooking canceled. Your selected seats have been released.\n";
            for (int index : selectedSeatsThisSession) {
                selectedShow.seats[index].isBooked = false;
            }
        }
    }
    else {
        std::cout << "\nNo seats were selected. Returning to main menu.\n";
    }

    std::cin.ignore(10000, '\n');
    std::cout << "Press Enter to return to the main menu...";
    std::cin.get();
}
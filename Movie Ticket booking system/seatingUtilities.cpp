#include "precompiler.h"

void displaySeatingChart(Show& show, int totalSeats) {
    // This part that initializes seats remains the same
    if (show.seats.empty()) {
        int seatsPerRow = 10;
        for (int i = 0; i < totalSeats; ++i) {
            show.seats.emplace_back(i / seatsPerRow + 1, i % seatsPerRow + 1);
        }
        srand(time(0));
        for (int i = 0; i < totalSeats / 4; ++i) {
            show.seats[rand() % totalSeats].isBooked = true;
        }
    }

    std::cout << "\n--- Seating Arrangement ---\n";
    std::cout << "      Screen This Way\n\n";

    int seatsPerRow = 10;
    for (size_t i = 0; i < show.seats.size(); ++i) {
        if (i % seatsPerRow == 0) {
            // Print row number at the beginning of each row
            if (i != 0) std::cout << "\n";
            std::cout << "Row " << std::setw(2) << show.seats[i].row << ": ";
        }

        int seatNum = show.seats[i].number;

        // Print the seat number with appropriate color
        if (show.seats[i].isBooked) {
            // Red for booked seats
            std::cout << "\033[31m" << std::setw(2) << seatNum << " \033[0m";
        }
        else {
            // Green for available seats
            std::cout << "\033[32m" << std::setw(2) << seatNum << " \033[0m";
        }
    }
    // Update the legend
    std::cout << "\n\nLegend: Green = Available | Red = Booked\n";
}

// Main function for seat selection process
void seatSelector() {
    if (cinemas.empty()) {
        std::cout << "No cinemas available to select seats from.\n";
        return;
    }

    // 1. Select Cinema
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

    // 2. Select Hall
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

    // 3. Select Movie
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

    // 4. Select Show
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

    // 5. Display the seating chart for the first time
    system("cls");
    displaySeatingChart(selectedShow, selectedCinema.seat);

    // 6. Interactive booking loop
    while (true) {
        std::cout << "\nEnter row and seat number to book (e.g., 3 5).\n";
        std::cout << "Enter 0 0 to finish selection: ";
        int row, seatNum;
        std::cin >> row >> seatNum;

        if (std::cin.fail()) {
            std::cout << "Invalid input. Please enter numbers only.\n";
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue; // Ask for input again
        }

        if (row == 0 || seatNum == 0) {
            std::cout << "Finished selecting seats.\n";
            break; // Exit the booking loop
        }

        int seatsPerRow = 10;
        // Calculate total rows, rounding up
        int totalRows = (selectedCinema.seat + seatsPerRow - 1) / seatsPerRow;

        // Validate that the chosen seat exists
        if (row < 1 || row > totalRows || seatNum < 1 || seatNum > seatsPerRow) {
            std::cout << "Invalid seat number. Please try again.\n";
            continue;
        }

        // Convert 2D coordinates to 1D vector index
        int seatIndex = (row - 1) * seatsPerRow + (seatNum - 1);

        if (seatIndex >= selectedCinema.seat) {
            std::cout << "Invalid seat number. Please try again.\n";
            continue;
        }

        // Check if the seat is already booked
        if (selectedShow.seats[seatIndex].isBooked) {
            std::cout << "Sorry, that seat is already booked. Please choose another.\n";
        } else {
            selectedShow.seats[seatIndex].isBooked = true;
            std::cout << "Seat (" << row << ", " << seatNum << ") booked successfully!\n";
            
            // Short pause to see the message
            std::cout << "Press Enter to continue...";
            std::cin.ignore(10000, '\n'); // Clear previous input
            std::cin.get(); // Wait for Enter key

            // Redisplay the updated chart
            system("cls");
            displaySeatingChart(selectedShow, selectedCinema.seat);
        }
    }
    // After the loop finishes, clear the final newline before returning to the menu
    std::cin.ignore(10000, '\n');
}
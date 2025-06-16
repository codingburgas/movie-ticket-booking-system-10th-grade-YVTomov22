#include "precompiler.h"

void userType(bool userChoice)
{

    if (userChoice)
    {
        std::cout << "Register user.";
    }
    else {
        std::cout << "Login user.";
    }

}

void addCinema() {
    Cinema newCinema;
    std::cin.ignore(); // Clear input buffer

    std::cout << "Enter city name: ";
    std::getline(std::cin, newCinema.city);

    std::cout << "Enter number of seats (1–100): ";
    std::cin >> newCinema.seat;

    if (std::cin.fail() || newCinema.seat <= 0 || newCinema.seat > 100) {
        std::cin.clear(); // Clear error state
        std::cin.ignore(1000, '\n'); // Discard invalid input
        std::cout << "Invalid seat input. Must be a number between 1 and 100.\n";
        return;
    }

    int hallCount;
    std::cout << "How many halls in the cinema? ";
    std::cin >> hallCount;
    std::cin.ignore();

    for (int i = 0; i < hallCount; ++i) {
        Hall newHall;
        std::cout << "Enter name for hall " << i + 1 << ": ";
        std::getline(std::cin, newHall.name);
        newCinema.halls.push_back(newHall);
    }

    newCinema.addedByUserID = currentUser.id;

    cinemas.push_back(newCinema);
    std::cout << "Cinema added successfully by user ID " << currentUser.id << "!\n";
}



// Adds a movie to a selected cinema and hall
void addMovie() {
    if (cinemas.empty()) {
        std::cout << "No cinemas available.\n";
        return;
    }

    // Select Cinema
    std::cout << "\nSelect a Cinema:\n";
    for (size_t i = 0; i < cinemas.size(); ++i) {
        std::cout << i + 1 << ". " << cinemas[i].city << "\n";
    }

    int cinemaIndex;
    std::cin >> cinemaIndex;
    if (cinemaIndex < 1 || cinemaIndex > cinemas.size()) {
        std::cout << "Invalid cinema selection.\n";
        return;
    }

    Cinema& selectedCinema = cinemas[cinemaIndex - 1];

    if (selectedCinema.halls.empty()) {
        std::cout << "No halls available in this cinema.\n";
        return;
    }

    // Select Hall
    std::cout << "\nSelect a Hall:\n";
    for (size_t i = 0; i < selectedCinema.halls.size(); ++i) {
        std::cout << i + 1 << ". " << selectedCinema.halls[i].name << "\n";
    }

    int hallIndex;
    std::cin >> hallIndex;
    if (hallIndex < 1 || hallIndex > selectedCinema.halls.size()) {
        std::cout << "Invalid hall selection.\n";
        return;
    }

    Hall& selectedHall = selectedCinema.halls[hallIndex - 1];

    // Get Movie Details
    Movie newMovie;
    std::cin.ignore(); // Clear buffer
    std::cout << "Enter movie title: ";
    std::getline(std::cin, newMovie.title);
    std::cout << "Enter language: ";
    std::getline(std::cin, newMovie.language);
    std::cout << "Enter genre: ";
    std::getline(std::cin, newMovie.genre);
    std::cout << "Enter release date: ";
    std::cin >> newMovie.releaseDate;

    // Add Shows
    int showCount;
    std::cout << "How many showtimes? ";
    std::cin >> showCount;
    std::cin.ignore();

    for (int i = 0; i < showCount; ++i) {
        Show show;
        std::cout << "Enter time for show " << i + 1 << ": ";
        std::getline(std::cin, show.time);
        show.hallName = selectedHall.name;
        newMovie.shows.push_back(show);
    }

    // Track who added it
    newMovie.addedByUserID = currentUser.id;

    // Save to Hall
    selectedHall.movies.push_back(newMovie);
    std::cout << "Movie added successfully by user ID " << currentUser.id << "!\n";
}


// Lists all cinemas and their halls
void listCinemasAndHalls() {
    bool found = false;

    for (auto& cinema : cinemas) {
        if (cinema.addedByUserID == currentUser.id) {
            found = true;
            std::cout << "City: " << cinema.city << "\n";
            for (auto& hall : cinema.halls) {
                std::cout << "  Hall: " << hall.name << "\n";
            }
        }
    }

    if (!found) {
        std::cout << "You haven't added any cinemas yet.\n";
    }
}


// Lists all showtimes for a given movie title
void listShowtimes() {
    std::string movieTitle;
    std::cin.ignore();
    std::cout << "Enter movie title: ";
    std::getline(std::cin, movieTitle);

    for (auto& cinema : cinemas) {
        for (auto& hall : cinema.halls) {
            for (auto& movie : hall.movies) {
                if (movie.title == movieTitle) {
                    std::cout << "In cinema: " << cinema.city
                        << ", hall: " << hall.name << "\n";
                    for (auto& show : movie.shows) {
                        std::cout << "  Time: " << show.time << "\n";
                    }
                }
            }
        }
    }
}

// Searches for movies by title, language, genre, or release year
void searchMovies() {
    std::string query;
    std::cin.ignore();
    std::cout << "Enter search keyword (title, language, genre, or year): ";
    std::getline(std::cin, query);

    int queryYear = -1;


    for (auto& cinema : cinemas) {
        for (auto& hall : cinema.halls) {
            for (auto& movie : hall.movies) {
                if (movie.title == query || movie.language == query ||
                    movie.genre == query || movie.releaseDate == queryYear) {
                    std::cout << "Movie: " << movie.title
                        << " | " << movie.language
                        << " | " << movie.genre
                        << " | " << movie.releaseDate
                        << " | Cinema: " << cinema.city
                        << " | Hall: " << hall.name << "\n";
                }
            }
        }
    }
}


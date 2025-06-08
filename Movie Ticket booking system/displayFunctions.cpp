#include "precompiler.h"

// Adds a new cinema with halls
void addCinema() {
    Cinema newCinema;
    std::cin.ignore(); // Clear newline buffer

    std::cout << "Enter city name: ";
    std::getline(std::cin, newCinema.city);

    std::cout << "Enter number of seats (e.g., 100): ";
    std::cin >> newCinema.seat;

    if (newCinema.seat <= 0 || newCinema.seat > 100) {
        std::cout << "Invalid seat input.\n";
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

    cinemas.push_back(newCinema);
    std::cout << "Cinema added successfully!\n";
}

// Adds a movie to a selected cinema and hall
void addMovie() {
    Show show;

    if (cinemas.empty()) {
        std::cout << "No cinemas available.\n";
        return;
    }

    // List cinemas
    std::cout << "\nSelect a Cinema:\n";
    for (size_t i = 0; i < cinemas.size(); ++i) {
        std::cout << i + 1 << ". " << cinemas[i].city << "\n";
    }

    int cinemaIndex;
    std::cin >> cinemaIndex;
    if (cinemaIndex < 1 || cinemaIndex > static_cast<int>(cinemas.size())) {
        std::cout << "Invalid cinema selection.\n";
        return;
    }

    Cinema& selectedCinema = cinemas[cinemaIndex - 1];

    if (selectedCinema.halls.empty()) {
        std::cout << "No halls available in this cinema.\n";
        return;
    }

    // List halls
    std::cout << "\nSelect a Hall:\n";
    for (size_t i = 0; i < selectedCinema.halls.size(); ++i) {
        std::cout << i + 1 << ". " << selectedCinema.halls[i].name << "\n";
    }

    int hallIndex;
    std::cin >> hallIndex;
    if (hallIndex < 1 || hallIndex > static_cast<int>(selectedCinema.halls.size())) {
        std::cout << "Invalid hall selection.\n";
        return;
    }

    Hall& selectedHall = selectedCinema.halls[hallIndex - 1];

    // Get movie details
    Movie newMovie;
    std::cin.ignore(); // Clear newline
    std::cout << "Enter movie title: ";
    std::getline(std::cin, newMovie.title);
    std::cout << "Enter language: ";
    std::getline(std::cin, newMovie.language);
    std::cout << "Enter genre: ";
    std::getline(std::cin, newMovie.genre);
    std::cout << "Enter release year (e.g., 2024): ";
    std::cin >> newMovie.releaseDate;

    if (newMovie.releaseDate < 1800 || newMovie.releaseDate > 2100) {
        std::cout << "Invalid release year.\n";
        return;
    }

    // Add showtimes
    int showCount;
    std::cout << "How many showtimes to add? ";
    std::cin >> showCount;
    std::cin.ignore();

    for (int i = 0; i < showCount; ++i) {
        std::cout << "Enter time for show " << i + 1 << ": ";
        std::getline(std::cin, show.time);
        show.hallName = selectedHall.name;
        newMovie.shows.push_back(show);
    }

    // Add movie to hall
    selectedHall.movies.push_back(newMovie);
    std::cout << "Movie added successfully!\n";
}

// Lists all cinemas and their halls
void listCinemasAndHalls() {
    for (const auto& cinema : cinemas) {
        std::cout << "City: " << cinema.city << "\n";
        for (const auto& hall : cinema.halls) {
            std::cout << "  Hall: " << hall.name << "\n";
        }
    }
}

// Lists all showtimes for a given movie title
void listShowtimes() {
    std::string movieTitle;
    std::cin.ignore(); // Clear buffer
    std::cout << "Enter movie title: ";
    std::getline(std::cin, movieTitle);

    for (const auto& cinema : cinemas) {
        for (const auto& hall : cinema.halls) {
            for (const auto& movie : hall.movies) {
                if (movie.title == movieTitle) {
                    std::cout << "In cinema: " << cinema.city
                        << ", hall: " << hall.name << "\n";
                    for (const auto& show : movie.shows) {
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
    try {
        queryYear = std::stoi(query);
    }
    catch (...) {
        // not a number; treat as string
    }

    for (const auto& cinema : cinemas) {
        for (const auto& hall : cinema.halls) {
            for (const auto& movie : hall.movies) {
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

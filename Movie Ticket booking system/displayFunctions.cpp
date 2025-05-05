#include "precompiler.h"

void listCinemasAndHalls() {
    for (const auto& cinema : cinemas) {
        std::cout << "City: " << cinema.city << "\n";
        for (const auto& hall : cinema.halls) {
            std::cout << "  Hall: " << hall.name << "\n";
        }
    }
}

void listShowtimes() {
    std::string movieTitle;
    std::cin.ignore(); // clear buffer
    std::cout << "Enter movie title: ";
    std::getline(std::cin, movieTitle);

    for (const auto& cinema : cinemas) {
        for (const auto& hall : cinema.halls) {
            for (const auto& movie : hall.movies) {
                if (movie.title == movieTitle) {
                    std::cout << "In cinema: " << cinema.city << ", hall: " << hall.name << "\n";
                    for (const auto& show : movie.shows) {
                        std::cout << "  Time: " << show.time << "\n";
                    }
                }
            }
        }
    }
}

void searchMovies() {
    std::string query;
    std::cin.ignore();
    std::cout << "Enter search keyword (title, language, genre, or date): ";
    std::getline(std::cin, query);

    for (const auto& cinema : cinemas) {
        for (const auto& hall : cinema.halls) {
            for (const auto& movie : hall.movies) {
                if (movie.title == query || movie.language == query ||
                    movie.genre == query || movie.releaseDate == query) {
                    std::cout << "Movie: " << movie.title << " | " << movie.language << " | " << movie.genre << " | " << movie.releaseDate << "\n";
                }
            }
        }
    }
}

#include "precompiler.h"

bool isNumber(const std::string& s) {
    if (s.empty()) return false;
    return std::all_of(s.begin(), s.end(), ::isdigit);
}


void addCinema() {
    if (currentUser.role != "admin") {
        std::cout << "Permission Denied: Only admins can add cinemas.\n";
        return;
    }
    Cinema newCinema;
    std::cin.ignore();

    std::cout << "Enter city name: ";
    std::getline(std::cin, newCinema.city);

    std::cout << "Enter number of seats (1�100): ";
    std::cin >> newCinema.seat;
    if (std::cin.fail() || newCinema.seat <= 0 || newCinema.seat > 100) {
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        std::cout << "Invalid seat input.\n";
        return;
    }

    int hallCount;
    std::cout << "How many halls? ";
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

    saveCinemasToFile();
    std::cout << "Cinema added successfully!\n";
}

void addMovie() {
    if (currentUser.role != "admin") {
        std::cout << "Permission Denied: Only admins can add movies.\n";
        return;
    }
    if (cinemas.empty()) {
        std::cout << "No cinemas available.\n";
        return;
    }

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

    Movie newMovie;
    std::cin.ignore();
    std::cout << "Enter movie title: ";
    std::getline(std::cin, newMovie.title);
    std::cout << "Enter language: ";
    std::getline(std::cin, newMovie.language);
    std::cout << "Enter genre: ";
    std::getline(std::cin, newMovie.genre);
    std::cout << "Enter release date: ";
    std::getline(std::cin, newMovie.releaseDate);

    std::cout << "Enter ticket price for this movie: ";
    std::cin >> newMovie.price;

    int showCount;
    std::cout << "How many showtimes? ";
    std::cin >> showCount;
    std::cin.ignore();

    for (int i = 0; i < showCount; ++i) {
        Show show;
        std::cout << "Enter time for show " << i + 1 << " (e.g., 18:30): ";
        std::getline(std::cin, show.time);
        show.hallName = selectedHall.name;
        newMovie.shows.push_back(show);
    }

    newMovie.addedByUserID = currentUser.id;
    selectedHall.movies.push_back(newMovie);

    std::ofstream file("movies.txt", std::ios::app);
    if (file.is_open()) {
        file << currentUser.id << ','
            << selectedCinema.city << ','
            << selectedHall.name << ','
            << newMovie.title << ','
            << newMovie.language << ','
            << newMovie.genre << ','
            << newMovie.releaseDate << ','
            << newMovie.price;

        for (const auto& show : newMovie.shows) {
            file << ',' << show.time;
        }
        file << '\n';
        file.close();
    }
    std::cout << "Movie added successfully!\n";
}

void loadMoviesFromFile() {
    std::ifstream file("movies.txt");
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string userIdStr, city, hallName, title, language, genre, releaseDate, priceStr, showTime;

        std::getline(iss, userIdStr, ',');
        std::getline(iss, city, ',');
        std::getline(iss, hallName, ',');
        std::getline(iss, title, ',');
        std::getline(iss, language, ',');
        std::getline(iss, genre, ',');
        std::getline(iss, releaseDate, ',');
        std::getline(iss, priceStr, ',');

        Movie movie;
        movie.addedByUserID = std::stoi(userIdStr);
        movie.title = title;
        movie.language = language;
        movie.genre = genre;
        movie.releaseDate = releaseDate;
        if (!priceStr.empty()) {
            try {
                movie.price = std::stod(priceStr);
            }
            catch (const std::invalid_argument& e) {
                movie.price = 10.0;
            }
        }
        else {
            movie.price = 10.0;
        }

        while (std::getline(iss, showTime, ',')) {
            Show show;
            show.time = showTime;
            show.hallName = hallName;
            movie.shows.push_back(show);
        }

        for (auto& cinema : cinemas) {
            if (cinema.city == city) {
                for (auto& hall : cinema.halls) {
                    if (hall.name == hallName) {
                        hall.movies.push_back(movie);
                    }
                }
            }
        }
    }
}

void listCinemasAndHalls() {
    std::ifstream inFile("cinemas.txt");
    if (!inFile.is_open() || inFile.peek() == std::ifstream::traits_type::eof()) {
        std::cout << "\nYou haven't added any cinemas yet.\n";
        return;
    }

    std::string line;
    int index = 1;
    while (std::getline(inFile, line)) {
        if (line.empty()) continue;

        std::cout << "\nCinema " << index++ << ":\n";
        std::cout << "  City: " << line << "\n";

        std::getline(inFile, line);
        std::cout << "  Seats: " << line << "\n";

        std::getline(inFile, line);
        int hallCount = std::stoi(line);

        if (hallCount > 0) {
            std::cout << "  Halls:\n";
            for (int i = 0; i < hallCount; ++i) {
                std::getline(inFile, line);
                std::cout << "    - " << line << "\n";
            }
        }
        else {
            std::cout << "  No halls added to this cinema.\n";
        }
        std::getline(inFile, line);
    }
    inFile.close();
}

void listShowtimes() {
    std::string movieTitle;
    std::cin.ignore();
    std::cout << "Enter movie title: ";
    std::getline(std::cin, movieTitle);

    bool found = false;
    for (auto& cinema : cinemas) {
        for (auto& hall : cinema.halls) {
            for (auto& movie : hall.movies) {
                if (movie.title == movieTitle) {
                    found = true;
                    std::cout << "In Cinema: " << cinema.city << ", Hall: " << hall.name << "\n";
                    for (auto& show : movie.shows) {
                        std::cout << "  Time: " << show.time << "\n";
                    }
                }
            }
        }
    }
    if (!found) {
        std::cout << "No showtimes found for '" << movieTitle << "'.\n";
    }
}

void searchMovies() {
    std::string query;
    std::cin.ignore();
    std::cout << "Enter search keyword (title, language, genre): ";
    std::getline(std::cin, query);

    bool found = false;
    for (auto& cinema : cinemas) {
        for (auto& hall : cinema.halls) {
            for (auto& movie : hall.movies) {
                if (movie.title.find(query) != std::string::npos ||
                    movie.language.find(query) != std::string::npos ||
                    movie.genre.find(query) != std::string::npos) {
                    found = true;
                    std::cout << "Movie: " << movie.title
                        << " | " << movie.language
                        << " | " << movie.genre
                        << " | " << movie.releaseDate
                        << " | Price: $" << std::fixed << std::setprecision(2) << movie.price
                        << " | Cinema: " << cinema.city
                        << " | Hall: " << hall.name << "\n";
                }
            }
        }
    }
    if (!found) {
        std::cout << "No movies found matching your query.\n";
    }
}

void saveCinemasToFile() {
    std::ofstream out("cinemas.txt");
    for (const auto& cinema : cinemas) {
        out << cinema.city << "\n";
        out << cinema.seat << "\n";
        out << cinema.halls.size() << "\n";
        for (const auto& hall : cinema.halls) {
            out << hall.name << "\n";
        }
        out << cinema.addedByUserID << "\n";
    }
    out.close();
}

void loadCinemasFromFile() {
    std::ifstream in("cinemas.txt");
    if (!in.is_open()) return;
    cinemas.clear();

    std::string line;
    while (std::getline(in, line)) {
        if (line.empty()) continue;

        Cinema cinema;
        cinema.city = line;

        if (!std::getline(in, line) || !isNumber(line)) continue;
        cinema.seat = std::stoi(line);

        if (!std::getline(in, line) || !isNumber(line)) continue;
        int hallCount = std::stoi(line);

        for (int i = 0; i < hallCount; ++i) {
            Hall hall;
            if (!std::getline(in, hall.name)) break;
            cinema.halls.push_back(hall);
        }

        if (!std::getline(in, line) || !isNumber(line)) continue;
        cinema.addedByUserID = std::stoi(line);

        cinemas.push_back(cinema);
    }
    in.close();
}

void saveMoviesToFile() {
    std::ofstream file("movies.txt");
    if (!file.is_open()) {
        std::cout << "Error: Could not open movies.txt for saving.\n";
        return;
    }

    for (const auto& cinema : cinemas) {
        for (const auto& hall : cinema.halls) {
            for (const auto& movie : hall.movies) {
                file << movie.addedByUserID << ','
                    << cinema.city << ','
                    << hall.name << ','
                    << movie.title << ','
                    << movie.language << ','
                    << movie.genre << ','
                    << movie.releaseDate << ','
                    << movie.price;

                for (const auto& show : movie.shows) {
                    file << ',' << show.time;
                }
                file << '\n';
            }
        }
    }
    file.close();
}

void deleteCinema() {
    if (currentUser.role != "admin") {
        std::cout << "Permission Denied.\n";
        return;
    }
    if (cinemas.empty()) {
        std::cout << "There are no cinemas to delete.\n";
        return;
    }

    std::cout << "\nSelect a Cinema to DELETE:\n";
    for (size_t i = 0; i < cinemas.size(); ++i) {
        std::cout << i + 1 << ". " << cinemas[i].city << "\n";
    }

    std::cout << "Enter 0 to cancel.\nChoose an option: ";
    int choice;
    std::cin >> choice;

    if (choice == 0) {
        std::cout << "Deletion canceled.\n";
        return;
    }

    if (std::cin.fail() || choice < 1 || choice > cinemas.size()) {
        std::cout << "Invalid selection.\n";
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        return;
    }

    cinemas.erase(cinemas.begin() + (choice - 1));

    saveCinemasToFile();
    saveMoviesToFile();

    std::cout << "Cinema and all its movies have been deleted successfully!\n";
}

void deleteMovie() {
    if (currentUser.role != "admin") {
        std::cout << "Permission Denied.\n";
        return;
    }

    if (cinemas.empty()) {
        std::cout << "No cinemas available.\n";
        return;
    }
    std::cout << "\nSelect a Cinema:\n";
    for (size_t i = 0; i < cinemas.size(); ++i) {
        std::cout << i + 1 << ". " << cinemas[i].city << "\n";
    }
    int cinemaIndex;
    std::cin >> cinemaIndex;
    if (std::cin.fail() || cinemaIndex < 1 || cinemaIndex > cinemas.size()) {return;}
    Cinema& selectedCinema = cinemas[cinemaIndex - 1];

    if (selectedCinema.halls.empty()) {return;}
    std::cout << "\nSelect a Hall:\n";
    for (size_t i = 0; i < selectedCinema.halls.size(); ++i) {
        std::cout << i + 1 << ". " << selectedCinema.halls[i].name << "\n";
    }
    int hallIndex;
    std::cin >> hallIndex;
    if (std::cin.fail() || hallIndex < 1 || hallIndex > selectedCinema.halls.size()) {return;}
    Hall& selectedHall = selectedCinema.halls[hallIndex - 1];

    if (selectedHall.movies.empty()) {
        std::cout << "No movies in this hall to delete.\n";
        return;
    }
    std::cout << "\nSelect a Movie to DELETE:\n";
    for (size_t i = 0; i < selectedHall.movies.size(); ++i) {
        std::cout << i + 1 << ". " << selectedHall.movies[i].title << "\n";
    }
    std::cout << "Enter 0 to cancel.\nChoose an option: ";
    int movieIndex;
    std::cin >> movieIndex;

    if (movieIndex == 0) {
        std::cout << "Deletion canceled.\n";
        return;
    }

    if (std::cin.fail() || movieIndex < 1 || movieIndex > selectedHall.movies.size()) {
        std::cout << "Invalid selection.\n";
        return;
    }

    selectedHall.movies.erase(selectedHall.movies.begin() + (movieIndex - 1));

    saveMoviesToFile();

    std::cout << "Movie deleted successfully!\n";
}

void viewCinemaReservations() {
    if (currentUser.role != "admin") {
        std::cout << "Permission Denied. This is an admin-only feature.\n";
        return;
    }
    if (cinemas.empty()) {
        std::cout << "There are no cinemas to view.\n";
        return;
    }

    std::cout << "\nSelect a Cinema to view its reservation status:\n";
    for (size_t i = 0; i < cinemas.size(); ++i) {
        std::cout << i + 1 << ". " << cinemas[i].city << "\n";
    }

    std::cout << "Enter 0 to cancel.\nChoose an option: ";
    int choice;
    std::cin >> choice;

    if (choice == 0) {
        std::cout << "Action canceled.\n";
        std::cin.ignore(10000, '\n');
        std::cin.get();
        return;
    }

    if (std::cin.fail() || choice < 1 || choice > cinemas.size()) {
        std::cout << "Invalid selection.\n";
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        return;
    }

    Cinema& selectedCinema = cinemas[choice - 1];
    system("cls");
    std::cout << "--- Visual Reservation Status for " << selectedCinema.city << " ---\n\n";

    bool foundAnyShows = false;
    for (auto& hall : selectedCinema.halls) {
        if (hall.movies.empty()) continue;

        for (auto& movie : hall.movies) {
            for (auto& show : movie.shows) {
                foundAnyShows = true;


                std::cout << "========================================================\n";
                std::cout << "Hall: " << hall.name << " | Movie: " << movie.title << " | Time: " << show.time << "\n";

                displaySeatingChart(show, selectedCinema.seat);

                std::cout << "\n";
            }
        }
    }

    if (!foundAnyShows) {
        std::cout << "No shows have been added to this cinema yet.\n";
    }

    std::cout << "Press Enter to return to the main menu...";
    std::cin.ignore(10000, '\n');
    std::cin.get();
}

void updateMovie() {
    if (currentUser.role != "admin") {
        std::cout << "Permission Denied.\n";
        return;
    }

    if (cinemas.empty()) {
        std::cout << "No cinemas available.\n";
        return;
    }
    std::cout << "\nSelect a Cinema:\n";
    for (size_t i = 0; i < cinemas.size(); ++i) { std::cout << i + 1 << ". " << cinemas[i].city << "\n"; }
    int cinemaIndex;
    std::cin >> cinemaIndex;
    if (std::cin.fail() || cinemaIndex < 1 || cinemaIndex > cinemas.size()) { return; }
    Cinema& selectedCinema = cinemas[cinemaIndex - 1];

    if (selectedCinema.halls.empty()) { return; }
    std::cout << "\nSelect a Hall:\n";
    for (size_t i = 0; i < selectedCinema.halls.size(); ++i) { std::cout << i + 1 << ". " << selectedCinema.halls[i].name << "\n"; }
    int hallIndex;
    std::cin >> hallIndex;
    if (std::cin.fail() || hallIndex < 1 || hallIndex > selectedCinema.halls.size()) { return; }
    Hall& selectedHall = selectedCinema.halls[hallIndex - 1];

    if (selectedHall.movies.empty()) {
        std::cout << "No movies in this hall to update.\n";
        return;
    }
    std::cout << "\nSelect a Movie to Update:\n";
    for (size_t i = 0; i < selectedHall.movies.size(); ++i) { std::cout << i + 1 << ". " << selectedHall.movies[i].title << "\n"; }
    int movieIndex;
    std::cin >> movieIndex;
    if (std::cin.fail() || movieIndex < 1 || movieIndex > selectedHall.movies.size()) { return; }

    Movie& movieToUpdate = selectedHall.movies[movieIndex - 1];

    bool isDoneUpdating = false;
    while (!isDoneUpdating) {
        system("cls");
        std::cout << "Updating Movie: " << movieToUpdate.title << "\n";
        std::cout << "Current Price: $" << std::fixed << std::setprecision(2) << movieToUpdate.price << "\n\n";

        std::cout << "What do you want to change?\n";
        std::cout << "1. Title\n";
        std::cout << "2. Genre\n";
        std::cout << "3. Release Date\n";
        std::cout << "4. Price\n";
        std::cout << "0. Finish Updating\n";
        std::cout << "Choose an option: ";

        int choice;
        std::cin >> choice;
        std::cin.ignore(10000, '\n');

        switch (choice) {
        case 1: {
            std::cout << "Enter new title: ";
            std::getline(std::cin, movieToUpdate.title);
            std::cout << "Title updated!\n";
            break;
        }
        case 2: {
            std::cout << "Enter new genre: ";
            std::getline(std::cin, movieToUpdate.genre);
            std::cout << "Genre updated!\n";
            break;
        }
        case 3: {
            std::cout << "Enter new release date: ";
            std::getline(std::cin, movieToUpdate.releaseDate);
            std::cout << "Release date updated!\n";
            break;
        }
        case 4: {
            std::cout << "Enter new price: ";
            std::cin >> movieToUpdate.price;
            std::cout << "Price updated!\n";
            break;
        }
        case 0:
            isDoneUpdating = true;
            break;
        default:
            std::cout << "Invalid choice. Please try again.\n";
            break;
        }
        if (!isDoneUpdating) {
            std::cout << "Press Enter to continue...";
            std::cin.get();
        }
    }

    saveMoviesToFile();
    std::cout << "\nAll changes have been saved!\n";
    std::cout << "Press Enter to return to the main menu...";
}
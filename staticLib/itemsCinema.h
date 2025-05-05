#pragma once

#include <iostream>
#include <vector>
#include <string>

// Movie structure
struct Show {
    std::string time;
    std::string hallName;
};

struct Movie {
    std::string title;
    std::string language;
    std::string genre;
    std::string releaseDate;
    std::vector<Show> shows;
};

struct Hall {
    std::string name;
    std::vector<Movie> movies;
};

struct Cinema {
    std::string city;
    std::vector<Hall> halls;
};

extern std::vector<Cinema> cinemas;

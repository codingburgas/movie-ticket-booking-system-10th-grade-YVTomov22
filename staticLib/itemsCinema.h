#pragma once

#include <iostream>
#include <vector>
#include <string>

struct User {
    int id;
    std::string username;
    std::string password;
};

extern User currentUser;
extern bool isLoggedIn;

// Movie structure
class Show {
public:
    std::string time;
    std::string hallName;
};

class Movie {
public:
    std::string title;
    std::string language;
    std::string genre;
    int releaseDate;
    std::vector<Show> shows;
};

class Hall {
public:
    std::string name;
    std::vector<Movie> movies;
};

class Cinema {
public:
    int seat;
    std::string city;
    std::vector<Hall> halls;
};

extern std::vector<Cinema> cinemas;

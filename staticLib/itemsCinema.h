#pragma once

#include <iostream>
#include <vector>
#include <string>

struct User {
    int id;
    std::string username;
    std::string password;
    std::string role; // "admin" or "user"
};


extern User currentUser;
extern bool isLoggedIn;

// Movie structure
class Show {
public:
    std::string time;
    std::string hallName;
};

struct Movie {
    std::string title;
    std::string language;
    std::string genre;
    int releaseDate;
    std::vector<Show> shows;
    int addedByUserID; // New field
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
    int addedByUserID;
};

extern std::vector<Cinema> cinemas;

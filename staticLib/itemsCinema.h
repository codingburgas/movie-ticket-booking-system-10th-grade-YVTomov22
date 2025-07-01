#pragma once

#include <iostream>
#include <vector>
#include <string>

class User {
public:
    int id;
    std::string username;
    std::string password;
    std::string role;
};

extern User currentUser;
extern bool isLoggedIn;

class Seat {
public:
    int row;
    int number;
    bool isBooked;

    Seat(int r, int num) : row(r), number(num), isBooked(false) {}
};

class Show {
public:
    std::string time;
    std::string hallName;
    std::vector<Seat> seats;
};

class Movie {
public:
    std::string title;
    std::string language;
    std::string genre;
    std::string releaseDate;
    std::vector<Show> shows;
    int addedByUserID;
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
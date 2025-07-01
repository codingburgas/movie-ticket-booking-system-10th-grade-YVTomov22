#include "precompiler.h"

std::vector<Cinema> cinemas;
User currentUser;
bool isLoggedIn = false;
bool gameOn = true;

int main() {
    
    loadCinemasFromFile();
    loadMoviesFromFile();

    while (!isLoggedIn) {
        showAuthMenu();
    }

    while (gameOn) {
        showMenu();
    }

}

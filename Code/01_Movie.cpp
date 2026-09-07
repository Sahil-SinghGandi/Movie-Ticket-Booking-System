#include <string>
using namespace std;

class Movie {
private:
    string title;
    string language;
    int durationMinutes;

public:
    // Compile-time polymorphism: overloaded constructors.
    Movie() {
        this->title = "";
        this->language = "";
        this->durationMinutes = 0;
    }

    Movie(string title, string language, int durationMinutes) {
        // this keyword: distinguishes object fields from constructor parameters.
        this->title = title;
        this->language = language;
        this->durationMinutes = durationMinutes;
    }

    string getTitle() const { return title; }
    string getLanguage() const { return language; }
    int getDurationMinutes() const { return durationMinutes; }
};

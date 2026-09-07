#include <string>
#include <vector>
using namespace std;

class Cinema {
private:
    string cinemaName;
    vector<Screen> screens;

public:
    Cinema(string cinemaName) {
        this->cinemaName = cinemaName;
    }

    void addScreen(const Screen& screen) {
        screens.push_back(screen);
    }

    string getCinemaName() const { return cinemaName; }
    const vector<Screen>& getScreens() const { return screens; }
};

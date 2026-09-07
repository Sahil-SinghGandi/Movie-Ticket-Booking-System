#include <string>
#include <vector>
using namespace std;

class ShowSeat;

class Show {
private:
    int showId;
    Movie* movie;
    Screen* screen;
    string startTime;
    vector<ShowSeat> showSeats;

public:
    Show(int showId, Movie* movie, Screen* screen, string startTime);
    int getShowId() const;
    Movie* getMovie() const;
    Screen* getScreen() const;
    string getStartTime() const;
    vector<ShowSeat>& getShowSeats();
    const vector<ShowSeat>& getShowSeats() const;
    ShowSeat* findShowSeat(const string& seatNumber);
    void displaySeatLayout() const;
};

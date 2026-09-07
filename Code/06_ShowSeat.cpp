#include <iostream>
#include <string>
using namespace std;

enum SeatStatus {
    AVAILABLE,
    BOOKED
};

class ShowSeat {
private:
    Seat* physicalSeat;
    SeatStatus status;

public:
    ShowSeat(Seat* physicalSeat) {
        this->physicalSeat = physicalSeat;
        this->status = AVAILABLE;
    }

    Seat* getPhysicalSeat() const { return physicalSeat; }
    string getSeatNumber() const { return physicalSeat->getSeatNumber(); }
    SeatType getSeatType() const { return physicalSeat->getSeatType(); }
    SeatStatus getStatus() const { return status; }
    bool isAvailable() const { return status == AVAILABLE; }

    // Encapsulation: seat status changes only through these controlled methods.
    bool book() {
        if (status == BOOKED) return false;
        status = BOOKED;
        return true;
    }

    void release() {
        status = AVAILABLE;
    }
};

Show::Show(int showId, Movie* movie, Screen* screen, string startTime) {
    this->showId = showId;
    this->movie = movie;
    this->screen = screen;
    this->startTime = startTime;
    const vector<Seat>& screenSeats = screen->getSeats();
    for (size_t i = 0; i < screenSeats.size(); i++) {
        showSeats.push_back(ShowSeat(const_cast<Seat*>(&screenSeats[i])));
    }
}

int Show::getShowId() const { return showId; }
Movie* Show::getMovie() const { return movie; }
Screen* Show::getScreen() const { return screen; }
string Show::getStartTime() const { return startTime; }
vector<ShowSeat>& Show::getShowSeats() { return showSeats; }
const vector<ShowSeat>& Show::getShowSeats() const { return showSeats; }

ShowSeat* Show::findShowSeat(const string& seatNumber) {
    for (size_t i = 0; i < showSeats.size(); i++) {
        if (showSeats[i].getSeatNumber() == seatNumber) return &showSeats[i];
    }
    return NULL;
}

void Show::displaySeatLayout() const {
    cout << "\n" << screen->getScreenName() << "   " << startTime << "   "
         << movie->getTitle() << "\n\n";
    cout << "[ ] = AVAILABLE, [X] = BOOKED\n";
    SeatType currentType = SILVER;
    bool rowStarted = false;
    for (size_t i = 0; i < showSeats.size(); i++) {
        if (!rowStarted || showSeats[i].getSeatType() != currentType) {
            if (rowStarted) cout << "\n";
            currentType = showSeats[i].getSeatType();
            cout << seatTypeToString(currentType) << "   ";
            rowStarted = true;
        }
        cout << showSeats[i].getSeatNumber()
             << (showSeats[i].isAvailable() ? "[ ] " : "[X] ");
    }
    cout << "\n";
}

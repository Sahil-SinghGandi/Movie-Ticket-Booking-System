#include <string>
using namespace std;

enum SeatType {
    SILVER,
    GOLD,
    PLATINUM
};

string seatTypeToString(SeatType type) {
    if (type == SILVER) return "SILVER";
    if (type == GOLD) return "GOLD";
    return "PLATINUM";
}

class Seat {
private:
    string seatNumber;
    SeatType seatType;

public:
    Seat(string seatNumber, SeatType seatType) {
        this->seatNumber = seatNumber;
        this->seatType = seatType;
    }

    string getSeatNumber() const { return seatNumber; }
    SeatType getSeatType() const { return seatType; }
};

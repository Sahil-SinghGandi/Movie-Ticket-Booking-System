#include <string>
#include <vector>
using namespace std;

enum BookingStatus {
    PENDING,
    CONFIRMED,
    FAILED,
    CANCELLED
};

string bookingStatusToString(BookingStatus status) {
    if (status == PENDING) return "PENDING";
    if (status == CONFIRMED) return "CONFIRMED";
    if (status == FAILED) return "FAILED";
    return "CANCELLED";
}

class Booking {
private:
    static int nextBookingNumber;
    string bookingId;
    Customer customer;
    Show* show;
    vector<ShowSeat*> bookedSeats;
    int totalAmount;
    BookingStatus status;

public:
    Booking(const Customer& customer, Show* show, const vector<ShowSeat*>& bookedSeats, int totalAmount)
        : customer(customer) {
        this->bookingId = "BK" + to_string(nextBookingNumber++);
        this->show = show;
        this->bookedSeats = bookedSeats;
        this->totalAmount = totalAmount;
        this->status = PENDING;
    }

    string getBookingId() const { return bookingId; }
    const Customer& getCustomer() const { return customer; }
    Show* getShow() const { return show; }
    const vector<ShowSeat*>& getBookedSeats() const { return bookedSeats; }
    int getTotalAmount() const { return totalAmount; }
    BookingStatus getStatus() const { return status; }

    void confirm() { status = CONFIRMED; }
    void fail() { status = FAILED; }

    void cancel() {
        status = CANCELLED;
        for (size_t i = 0; i < bookedSeats.size(); i++) {
            bookedSeats[i]->release();
        }
    }
};

// Static member: all bookings share one counter for unique IDs.
int Booking::nextBookingNumber = 1001;

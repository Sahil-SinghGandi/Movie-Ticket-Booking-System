#include <iostream>
#include <string>
using namespace std;

class TicketPrinter {
public:
    void printTicket(const Booking& booking) const {
        cout << "\n=============== TICKET ===============\n";
        cout << "Booking ID : " << booking.getBookingId() << "\n";
        cout << "Customer   : " << booking.getCustomer().getName() << "\n";
        cout << "Movie      : " << booking.getShow()->getMovie()->getTitle() << "\n";
        cout << "Screen     : " << booking.getShow()->getScreen()->getScreenName() << "\n";
        cout << "Time       : " << booking.getShow()->getStartTime() << "\n";
        cout << "Seats      : " << seatList(booking.getBookedSeats()) << "\n";
        cout << "Amount     : Rs." << booking.getTotalAmount() << "\n";
        cout << "Status     : " << bookingStatusToString(booking.getStatus()) << "\n";
        cout << "======================================\n";
    }

private:
    string seatList(const vector<ShowSeat*>& seats) const {
        string result = "";
        for (size_t i = 0; i < seats.size(); i++) {
            if (i > 0) result += ", ";
            result += seats[i]->getSeatNumber();
        }
        return result;
    }
};

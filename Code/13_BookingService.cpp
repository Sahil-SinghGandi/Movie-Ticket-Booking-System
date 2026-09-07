#include <iostream>
#include <vector>
using namespace std;

class BookingService {
private:
    PriceCalculator priceCalculator;
    TicketPrinter ticketPrinter;
    vector<Booking*> bookings;

public:
    ~BookingService() {
        for (size_t i = 0; i < bookings.size(); i++) delete bookings[i];
    }

    // Association: Customer uses BookingService, but neither owns the other.
    Booking* bookSeats(Customer* customer, Show* show, const vector<string>& seatNumbers, Payment& payment) {
        vector<ShowSeat*> selectedSeats;
        if (!validateSeats(show, seatNumbers, selectedSeats)) return NULL;

        for (size_t i = 0; i < selectedSeats.size(); i++) selectedSeats[i]->book();
        int total = priceCalculator.calculateTotal(selectedSeats);
        printPriceBreakup(selectedSeats);

        Booking* booking = new Booking(*customer, show, selectedSeats, total);
        bookings.push_back(booking);

        // Runtime polymorphism: Payment reference can point to UPI/Card/Cash behavior.
        bool isPaid = payment.pay(total);
        if (!isPaid) {
            releaseSeats(selectedSeats);
            booking->fail();
            cout << "Booking failed. Seats released.\n";
            return booking;
        }

        booking->confirm();
        ticketPrinter.printTicket(*booking);
        return booking;
    }

    bool cancelBooking(const string& bookingId) {
        Booking* booking = findBooking(bookingId);
        if (booking == NULL) {
            cout << "Booking ID not found.\n";
            return false;
        }
        if (booking->getStatus() != CONFIRMED) {
            cout << "Only confirmed bookings can be cancelled.\n";
            return false;
        }
        booking->cancel();
        cout << "Booking cancelled. Seats are AVAILABLE again.\n";
        return true;
    }

    void printMyTickets() const {
        if (bookings.empty()) {
            cout << "No bookings found.\n";
            return;
        }
        for (size_t i = 0; i < bookings.size(); i++) ticketPrinter.printTicket(*bookings[i]);
    }

private:
    bool validateSeats(Show* show, const vector<string>& seatNumbers, vector<ShowSeat*>& selectedSeats) {
        if (seatNumbers.empty()) {
            cout << "Select at least one seat.\n";
            return false;
        }
        for (size_t i = 0; i < seatNumbers.size(); i++) {
            ShowSeat* seat = show->findShowSeat(seatNumbers[i]);
            if (seat == NULL) {
                cout << "Invalid seat number: " << seatNumbers[i] << "\n";
                return false;
            }
            if (!seat->isAvailable()) {
                cout << "Seat " << seatNumbers[i] << " is already BOOKED. Entire booking rejected.\n";
                return false;
            }
            selectedSeats.push_back(seat);
        }
        return true;
    }

    void releaseSeats(const vector<ShowSeat*>& seats) {
        for (size_t i = 0; i < seats.size(); i++) seats[i]->release();
    }

    void printPriceBreakup(const vector<ShowSeat*>& seats) const {
        cout << "\nPrice Breakup\n";
        for (size_t i = 0; i < seats.size(); i++) {
            cout << seats[i]->getSeatNumber() << " "
                 << seatTypeToString(seats[i]->getSeatType()) << "    Rs."
                 << priceCalculator.priceForSeat(seats[i]) << "\n";
        }
        cout << "TOTAL        Rs." << priceCalculator.calculateTotal(seats) << "\n";
    }

    Booking* findBooking(const string& bookingId) {
        for (size_t i = 0; i < bookings.size(); i++) {
            if (bookings[i]->getBookingId() == bookingId) return bookings[i];
        }
        return NULL;
    }
};

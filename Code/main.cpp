#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

#include "01_Movie.cpp"
#include "02_Seat.cpp"
#include "03_Screen.cpp"
#include "04_Cinema.cpp"
#include "05_Show.cpp"
#include "06_ShowSeat.cpp"
#include "07_Customer.cpp"
#include "08_Booking.cpp"
#include "09_Payment.cpp"
#include "10_PaymentTypes.cpp"
#include "11_PriceCalculator.cpp"
#include "12_TicketPrinter.cpp"
#include "13_BookingService.cpp"

vector<string> splitSeats(string input) {
    vector<string> seats;
    string token;
    stringstream stream(input);
    while (getline(stream, token, ',')) {
        if (!token.empty()) seats.push_back(token);
    }
    return seats;
}

int readNumber(string prompt) {
    string input;
    cout << prompt;
    getline(cin, input);
    stringstream stream(input);
    int value = -1;
    if (!(stream >> value)) return -1;
    return value;
}

void seedSeats(Screen& screen) {
    screen.addSeat(Seat("A1", SILVER));
    screen.addSeat(Seat("A2", SILVER));
    screen.addSeat(Seat("A3", SILVER));
    screen.addSeat(Seat("A4", SILVER));
    screen.addSeat(Seat("B1", GOLD));
    screen.addSeat(Seat("B2", GOLD));
    screen.addSeat(Seat("B3", GOLD));
    screen.addSeat(Seat("B4", GOLD));
    screen.addSeat(Seat("C1", PLATINUM));
    screen.addSeat(Seat("C2", PLATINUM));
}

Payment* createPayment() {
    cout << "\nPay by:\n1. UPI\n2. Card\n3. Cash\n";
    int choice = readNumber("Choice: ");
    int successChoice = readNumber("Simulate payment success? 1.Yes 2.No: ");
    bool shouldSucceed = (successChoice == 1);
    if (choice == 1) return new UpiPayment(shouldSucceed);
    if (choice == 2) return new CardPayment(shouldSucceed);
    if (choice == 3) return new CashPayment(shouldSucceed);
    cout << "Invalid payment method.\n";
    return NULL;
}

int chooseMovie(const vector<Movie>& movies) {
    cout << "\nCurrently Playing Movies\n";
    for (size_t i = 0; i < movies.size(); i++) {
        cout << "[" << i + 1 << "] " << movies[i].getTitle() << "    "
             << movies[i].getLanguage() << "    "
             << movies[i].getDurationMinutes() << " min\n";
    }
    int choice = readNumber("Select movie: ");
    if (choice < 1 || choice > (int)movies.size()) {
        cout << "Invalid movie choice.\n";
        return -1;
    }
    return choice - 1;
}

Show* chooseShow(vector<Show>& shows, int movieIndex, const vector<Movie>& movies) {
    vector<Show*> matchingShows;
    cout << "\nShows for " << movies[movieIndex].getTitle() << "\n";
    for (size_t i = 0; i < shows.size(); i++) {
        if (shows[i].getMovie() == &movies[movieIndex]) {
            matchingShows.push_back(&shows[i]);
            cout << "[" << matchingShows.size() << "] "
                 << shows[i].getScreen()->getScreenName() << "   "
                 << shows[i].getStartTime() << "\n";
        }
    }
    int choice = readNumber("Select show: ");
    if (choice < 1 || choice > (int)matchingShows.size()) {
        cout << "Invalid show choice.\n";
        return NULL;
    }
    return matchingShows[choice - 1];
}

void handleBooking(vector<Movie>& movies, vector<Show>& shows, BookingService& service) {
    int movieIndex = chooseMovie(movies);
    if (movieIndex == -1) return;
    Show* selectedShow = chooseShow(shows, movieIndex, movies);
    if (selectedShow == NULL) return;
    selectedShow->displaySeatLayout();

    string name, phone, seatInput;
    cout << "Customer name: ";
    getline(cin, name);
    cout << "Phone: ";
    getline(cin, phone);
    cout << "Seats (example A1,B2): ";
    getline(cin, seatInput);

    Payment* payment = createPayment();
    if (payment == NULL) return;
    Customer customer(name, phone);
    service.bookSeats(&customer, selectedShow, splitSeats(seatInput), *payment);
    delete payment;
}

void showMenu() {
    cout << "\n===== MOVIE TICKET BOOKING =====\n";
    cout << "1. Movies\n";
    cout << "2. Book\n";
    cout << "3. Cancel\n";
    cout << "4. My tickets\n";
    cout << "0. Exit\n";
}

int main() {
    Movie movieOne("3 Idiots", "Hindi", 170);
    Movie movieTwo("Interstellar", "English", 169);
    vector<Movie> movies;
    movies.push_back(movieOne);
    movies.push_back(movieTwo);

    Screen screenOne("Screen-1");
    Screen screenTwo("Screen-2");
    seedSeats(screenOne);
    seedSeats(screenTwo);

    Cinema cinema("PVR City Cinema");
    cinema.addScreen(screenOne);
    cinema.addScreen(screenTwo);

    vector<Screen> screens = cinema.getScreens();
    vector<Show> shows;
    shows.push_back(Show(1, &movies[0], &screens[0], "06:00 PM"));
    shows.push_back(Show(2, &movies[0], &screens[1], "09:00 PM"));
    shows.push_back(Show(3, &movies[1], &screens[0], "07:30 PM"));

    BookingService service;
    int choice = -1;
    while (choice != 0) {
        showMenu();
        choice = readNumber("Choice: ");
        if (choice == 1) chooseMovie(movies);
        else if (choice == 2) handleBooking(movies, shows, service);
        else if (choice == 3) {
            string id;
            cout << "Booking ID to cancel: ";
            getline(cin, id);
            service.cancelBooking(id);
        } else if (choice == 4) service.printMyTickets();
        else if (choice == 0) cout << "Thank you.\n";
        else cout << "Invalid menu choice.\n";
    }
    return 0;
}

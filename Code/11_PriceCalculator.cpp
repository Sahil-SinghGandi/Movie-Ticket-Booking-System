#include <vector>
using namespace std;

const int SILVER_PRICE = 150;
const int GOLD_PRICE = 250;
const int PLATINUM_PRICE = 400;

class PriceCalculator {
public:
    int priceForSeat(const ShowSeat* seat) const {
        if (seat->getSeatType() == SILVER) return SILVER_PRICE;
        if (seat->getSeatType() == GOLD) return GOLD_PRICE;
        return PLATINUM_PRICE;
    }

    int calculateTotal(const vector<ShowSeat*>& seats) const {
        int total = 0;
        for (size_t i = 0; i < seats.size(); i++) total += priceForSeat(seats[i]);
        return total;
    }
};

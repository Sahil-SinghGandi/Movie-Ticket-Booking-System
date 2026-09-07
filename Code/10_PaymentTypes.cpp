#include <iostream>
using namespace std;

class UpiPayment : public Payment {
private:
    bool shouldSucceed;

public:
    UpiPayment(bool shouldSucceed) {
        this->shouldSucceed = shouldSucceed;
    }

    bool pay(int amount) {
        if (shouldSucceed) cout << "[UPI] Rs." << amount << " paid successfully\n";
        else cout << "[UPI] Payment failed\n";
        return shouldSucceed;
    }

    string getMethodName() const { return "UPI"; }
};

class CardPayment : public Payment {
private:
    bool shouldSucceed;

public:
    CardPayment(bool shouldSucceed) {
        this->shouldSucceed = shouldSucceed;
    }

    bool pay(int amount) {
        if (shouldSucceed) cout << "[Card] Rs." << amount << " paid successfully\n";
        else cout << "[Card] Payment failed\n";
        return shouldSucceed;
    }

    string getMethodName() const { return "Card"; }
};

class CashPayment : public Payment {
private:
    bool shouldSucceed;

public:
    CashPayment(bool shouldSucceed) {
        this->shouldSucceed = shouldSucceed;
    }

    bool pay(int amount) {
        if (shouldSucceed) cout << "[Cash] Rs." << amount << " paid successfully\n";
        else cout << "[Cash] Payment failed\n";
        return shouldSucceed;
    }

    string getMethodName() const { return "Cash"; }
};

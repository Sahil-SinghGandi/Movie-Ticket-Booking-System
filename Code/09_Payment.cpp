class Payment {
public:
    // Abstraction: every payment type must provide pay(amount).
    virtual bool pay(int amount) = 0;
    virtual string getMethodName() const = 0;
    virtual ~Payment() {}
};

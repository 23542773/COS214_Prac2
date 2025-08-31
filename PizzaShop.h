#ifndef PIZZASHOP_H
#define PIZZASHOP_H

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <list>

// Forward declarations
class Pizza;
class Topping;
class ToppingGroup;
class BasePizza;
class PizzaDecorator;
class ExtraCheese;
class StuffedCrust;
class DiscountStrategy;
class RegularPrice;
class BulkDiscount;
class FamilyDiscount;
class Observer;
class Customer;
class Website;
class Menu;
class PizzaMenu;
class SpecialsMenu;
class OrderPhase;
class OrderStarted;
class Pending;
class Preparing;
class Ready;

// ==================== COMPOSITE PATTERN ====================
class Pizza {
protected:
    double price;
    std::string name;
    
public:
    Pizza(double p, std::string n);
    virtual ~Pizza();
    virtual std::string getName() = 0;
    virtual double getPrice() = 0;
};

class Topping : public Pizza {
public:
    Topping(double p, std::string n);
    std::string getName() override;
    double getPrice() override;
};

class ToppingGroup : public Pizza {
private:
    std::vector<Pizza*> toppings;
    
public:
    ToppingGroup(std::string n);
    ~ToppingGroup();
    void add(Pizza* component);
    std::string getName() override;
    double getPrice() override;
};

// ==================== DECORATOR PATTERN ====================
class BasePizza : public Pizza {
private:
    Pizza* toppings;
    
public:
    BasePizza(Pizza* t);
    ~BasePizza();
    double getPrice() override;
    std::string getName() override;
    void printPizza();
};

class PizzaDecorator : public Pizza {
protected:
    Pizza* pizza;
    
public:
    PizzaDecorator(Pizza* p);
    virtual ~PizzaDecorator();
};

class ExtraCheese : public PizzaDecorator {
private:
    double extraCost;
    
public:
    ExtraCheese(Pizza* p, double cost = 12.00);
    double getPrice() override;
    std::string getName() override;
    void printPizza();
};

class StuffedCrust : public PizzaDecorator {
private:
    double extraCost;
    
public:
    StuffedCrust(Pizza* p, double cost = 20.00);
    double getPrice() override;
    std::string getName() override;
    void printPizza();
};

// ==================== STRATEGY PATTERN ====================
class DiscountStrategy {
public:
    virtual ~DiscountStrategy();
    virtual double applyDiscount(double originalPrice) = 0;
    virtual std::string getStrategyName() = 0;
};

class RegularPrice : public DiscountStrategy {
public:
    double applyDiscount(double originalPrice) override;
    std::string getStrategyName() override;
};

class BulkDiscount : public DiscountStrategy {
public:
    double applyDiscount(double originalPrice) override;
    std::string getStrategyName() override;
};

class FamilyDiscount : public DiscountStrategy {
public:
    double applyDiscount(double originalPrice) override;
    std::string getStrategyName() override;
};

// ==================== OBSERVER PATTERN ====================
class Observer {
public:
    virtual ~Observer();
    virtual void update(const std::string& message) = 0;
};

class Customer : public Observer {
private:
    std::string name;
    
public:
    Customer(std::string n);
    void update(const std::string& message) override;
};

class Website : public Observer {
public:
    Website();
    void update(const std::string& message) override;
};

class Menu {
protected:
    std::vector<Observer*> observers;
    std::vector<Pizza*> pizzas;
    
public:
    virtual ~Menu();
    void addObserver(Observer* observer);
    void removeObserver(Observer* observer);
    virtual void addPizza(Pizza* pizza) = 0;
    virtual void removePizza(Pizza* pizza) = 0;
    virtual void notifyObservers(const std::string& message) = 0;
};

class PizzaMenu : public Menu {
public:
    void addPizza(Pizza* pizza) override;
    void removePizza(Pizza* pizza) override;
    void notifyObservers(const std::string& message) override;
};

class SpecialsMenu : public Menu {
public:
    void addPizza(Pizza* pizza) override;
    void removePizza(Pizza* pizza) override;
    void notifyObservers(const std::string& message) override;
};

// ==================== STATE PATTERN ====================
class PlaceOrder;

class OrderPhase {
public:
    virtual ~OrderPhase();
    virtual void handleState(PlaceOrder* order) = 0;
    virtual std::string getStateName() const = 0;
};

class OrderStarted : public OrderPhase {
public:
    void handleState(PlaceOrder* order) override;
    std::string getStateName() const override;
};

class Pending : public OrderPhase {
public:
    void handleState(PlaceOrder* order) override;
    std::string getStateName() const override;
};

class Preparing : public OrderPhase {
public:
    void handleState(PlaceOrder* order) override;
    std::string getStateName() const override;
};

class Ready : public OrderPhase {
public:
    void handleState(PlaceOrder* order) override;
    std::string getStateName() const override;
};

// ==================== MERGED PLACEORDER CLASS ====================
class PlaceOrder {
private:
    std::vector<Pizza*> pizzas;
    DiscountStrategy* discountStrategy;
    OrderPhase* currentState;
    
public:
    PlaceOrder();
    ~PlaceOrder();
    
    // Order management methods
    void addPizza(Pizza* pizza);
    void setDiscountStrategy(DiscountStrategy* strategy);
    double calculateTotal();
    int getPizzaCount();
    double getTotal();
    
    // State management methods
    void processOrder();
    void setState(OrderPhase* newState);
    std::string getStatus() const;
    
    // Additional utility methods
    void printOrderSummary();
    void clearOrder();
};

// ==================== Creation methods ====================
class PizzaFactory {
public:
    static Pizza* createPepperoniPizza();
    static Pizza* createVegetarianPizza();
    static Pizza* createMeatLoversPizza();
    static Pizza* createVegetarianDeluxePizza();
    static Pizza* addExtraCheese(Pizza* pizza);
    static Pizza* addStuffedCrust(Pizza* pizza);
};

#endif // PIZZASHOP_H
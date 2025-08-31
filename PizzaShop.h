
#ifndef PIZZASHOP_H
#define PIZZASHOP_H

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <list>
#include <memory>

// Forward declarations
class PizzaComponent;
class Topping;
class ToppingGroup;
class Pizza;
class BasePizza;
class PizzaDecorator;
class ExtraCheese;
class StuffedCrust;
class DiscountStrategy;
class RegularPrice;
class BulkDiscount;
class FamilyDiscount;
class PlaceOrder;
class Observer;
class Customer;
class Website;
class Menu;
class PizzaMenu;
class SpecialsMenu;
class OrderState;
class OrderStartedState;
class PendingState;
class PreparingState;
class ReadyState;
class Order;

// ==================== COMPOSITE PATTERN ====================
class PizzaComponent {
protected:
    double price;
    std::string name;
    
public:
    PizzaComponent(double p, std::string n);
    virtual ~PizzaComponent();
    virtual std::string getName() = 0;
    virtual double getPrice() = 0;
};

class Topping : public PizzaComponent {
public:
    Topping(double p, std::string n);
    std::string getName() override;
    double getPrice() override;
};

class ToppingGroup : public PizzaComponent {
private:
    std::vector<PizzaComponent*> toppings;
    
public:
    ToppingGroup(std::string n);
    ~ToppingGroup();
    void add(PizzaComponent* component);
    std::string getName() override;
    double getPrice() override;
};

// ==================== DECORATOR PATTERN ====================
class Pizza {
public:
    virtual ~Pizza();
    virtual double getPrice() = 0;
    virtual std::string getName() = 0;
    virtual void printPizza() = 0;
};

class BasePizza : public Pizza {
private:
    PizzaComponent* toppings;
    
public:
    BasePizza(PizzaComponent* t);
    ~BasePizza();
    double getPrice() override;
    std::string getName() override;
    void printPizza() override;
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
    void printPizza() override;
};

class StuffedCrust : public PizzaDecorator {
private:
    double extraCost;
    
public:
    StuffedCrust(Pizza* p, double cost = 20.00);
    double getPrice() override;
    std::string getName() override;
    void printPizza() override;
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
class Order;

class OrderState {
public:
    virtual ~OrderState();
    virtual void handleState(Order* order) = 0;
    virtual std::string getStateName() const = 0;
};

class OrderStartedState : public OrderState {
public:
    void handleState(Order* order) override;
    std::string getStateName() const override;
};

class PendingState : public OrderState {
public:
    void handleState(Order* order) override;
    std::string getStateName() const override;
};

class PreparingState : public OrderState {
public:
    void handleState(Order* order) override;
    std::string getStateName() const override;
};

class ReadyState : public OrderState {
public:
    void handleState(Order* order) override;
    std::string getStateName() const override;
};

// ==================== PLACE ORDER & ORDER ====================
class PlaceOrder {
private:
    DiscountStrategy* discountStrategy;
    std::vector<Pizza*> pizzas;
    
public:
    PlaceOrder();
    ~PlaceOrder();
    void addPizza(Pizza* pizza);
    void setDiscountStrategy(DiscountStrategy* strategy);
    double calculateTotal();
    int getPizzaCount();
    void processOrder();
};

class Order {
private:
    std::vector<Pizza*> pizzas;
    DiscountStrategy* discountStrategy;
    OrderState* currentState;
    PlaceOrder* placeOrder;
    
public:
    Order();
    ~Order();
    void addPizza(Pizza* pizza);
    void setDiscountStrategy(DiscountStrategy* strategy);
    void setPlaceOrder(PlaceOrder* po);
    double getTotal();
    int getPizzaCount();
    void setState(OrderState* newState);
    void processOrder();
    std::string getStatus() const;
};

// ==================== PIZZA FACTORY ====================
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
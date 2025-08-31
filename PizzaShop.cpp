#include "PizzaShop.h"
#include <cstdlib>
#include <ctime>
#include <algorithm>

// ==================== COMPOSITE PATTERN IMPLEMENTATION ====================
Pizza::Pizza(double p, std::string n) : price(p), name(n) {}
Pizza::~Pizza() {}

Topping::Topping(double p, std::string n) : Pizza(p, n) {}
std::string Topping::getName() { return name; }
double Topping::getPrice() { return price; }

ToppingGroup::ToppingGroup(std::string n) : Pizza(0, n) {}
ToppingGroup::~ToppingGroup() {
    for (auto topping : toppings) {
        delete topping;
    }
}
void ToppingGroup::add(Pizza* component) {
    toppings.push_back(component);
    price += component->getPrice();
}
std::string ToppingGroup::getName() {
    std::string result = name + " (";
    for (size_t i = 0; i < toppings.size(); i++) {
        result += toppings[i]->getName();
        if (i < toppings.size() - 1) result += ", ";
    }
    result += ")";
    return result;
}
double ToppingGroup::getPrice() { return price; }

// ==================== DECORATOR PATTERN IMPLEMENTATION ====================
BasePizza::BasePizza(Pizza* t) : Pizza(t->getPrice(), t->getName()), toppings(t) {}
BasePizza::~BasePizza() { delete toppings; }
double BasePizza::getPrice() { return toppings->getPrice(); }
std::string BasePizza::getName() { return toppings->getName(); }
void BasePizza::printPizza() {
    std::cout << "Pizza: " << getName() << " - R" << getPrice() << std::endl;
}

PizzaDecorator::PizzaDecorator(Pizza* p) : Pizza(p->getPrice(), p->getName()), pizza(p) {}
PizzaDecorator::~PizzaDecorator() { delete pizza; }

ExtraCheese::ExtraCheese(Pizza* p, double cost) : PizzaDecorator(p), extraCost(cost) {}
double ExtraCheese::getPrice() { return pizza->getPrice() + extraCost; }
std::string ExtraCheese::getName() { return pizza->getName() + " with Extra Cheese"; }
void ExtraCheese::printPizza() {
    std::cout << "Pizza: " << getName() << " - R" << getPrice() << std::endl;
}

StuffedCrust::StuffedCrust(Pizza* p, double cost) : PizzaDecorator(p), extraCost(cost) {}
double StuffedCrust::getPrice() { return pizza->getPrice() + extraCost; }
std::string StuffedCrust::getName() { return pizza->getName() + " with Stuffed Crust"; }
void StuffedCrust::printPizza() {
    std::cout << "Pizza: " << getName() << " - R" << getPrice() << std::endl;
}

// ==================== STRATEGY PATTERN IMPLEMENTATION ====================
DiscountStrategy::~DiscountStrategy() {}

double RegularPrice::applyDiscount(double originalPrice) { return originalPrice; }
std::string RegularPrice::getStrategyName() { return "Regular Price (0% discount)"; }

double BulkDiscount::applyDiscount(double originalPrice) { return originalPrice * 0.9; }
std::string BulkDiscount::getStrategyName() { return "Bulk Discount (10% discount)"; }

double FamilyDiscount::applyDiscount(double originalPrice) { return originalPrice * 0.85; }
std::string FamilyDiscount::getStrategyName() { return "Family Discount (15% discount)"; }

// ==================== OBSERVER PATTERN IMPLEMENTATION ====================
Observer::~Observer() {}

Customer::Customer(std::string n) : name(n) {}
void Customer::update(const std::string& message) {
    std::cout << "Customer " << name << " notified: " << message << std::endl;
}

Website::Website() {}
void Website::update(const std::string& message) {
    std::cout << "Website updated: " << message << std::endl;
}

Menu::~Menu() {
    observers.clear();
    pizzas.clear();
}

void Menu::addObserver(Observer* observer) { 
    observers.push_back(observer); 
}

void Menu::removeObserver(Observer* observer) {
    auto it = std::find(observers.begin(), observers.end(), observer);
    if (it != observers.end()) {
        observers.erase(it);
    }
}

void PizzaMenu::addPizza(Pizza* pizza) {
    pizzas.push_back(pizza);
    notifyObservers("New pizza added to menu: " + pizza->getName());
}

void PizzaMenu::removePizza(Pizza* pizza) {
    auto it = std::find(pizzas.begin(), pizzas.end(), pizza);
    if (it != pizzas.end()) {
        pizzas.erase(it);
        notifyObservers("Pizza removed from menu: " + pizza->getName());
    }
}

void PizzaMenu::notifyObservers(const std::string& message) {
    for (auto observer : observers) {
        observer->update(message);
    }
}

void SpecialsMenu::addPizza(Pizza* pizza) {
    pizzas.push_back(pizza);
    notifyObservers("New special added: " + pizza->getName());
}

void SpecialsMenu::removePizza(Pizza* pizza) {
    auto it = std::find(pizzas.begin(), pizzas.end(), pizza);
    if (it != pizzas.end()) {
        pizzas.erase(it);
        notifyObservers("Special removed: " + pizza->getName());
    }
}

void SpecialsMenu::notifyObservers(const std::string& message) {
    for (auto observer : observers) {
        observer->update(message);
    }
}

// ==================== STATE PATTERN IMPLEMENTATION ====================
OrderPhase::~OrderPhase() {}

void OrderStarted::handleState(PlaceOrder* order) {
    std::cout << "Order has been received and is starting...\n";
    order->setState(new Pending());
}
std::string OrderStarted::getStateName() const { return "ORDER STARTED"; }

void Pending::handleState(PlaceOrder* order) {
    std::cout << "Order is pending (e.g., awaiting kitchen availability)...\n";
    order->setState(new Preparing());
}
std::string Pending::getStateName() const { return "PENDING"; }

void Preparing::handleState(PlaceOrder* order) {
    std::cout << "Pizza is being prepared...\n";
    
    bool hasIssue = (std::rand() % 100) < 20;
    
    if (hasIssue) {
        std::cout << "*** Issue discovered! Moving back to PENDING. ***\n";
        order->setState(new Pending());
    } else {
        std::cout << "Preparation complete! Moving to READY.\n";
        order->setState(new Ready());
    }
}
std::string Preparing::getStateName() const { return "PREPARING"; }

void Ready::handleState(PlaceOrder* order) {
    (void)order; // Suppress unused parameter warning
    std::cout << "ORDER IS READY FOR PICKUP! :)\n";
}
std::string Ready::getStateName() const { return "READY"; }

// ==================== MERGED PLACEORDER IMPLEMENTATION ====================
PlaceOrder::PlaceOrder() : discountStrategy(new RegularPrice()), currentState(new OrderStarted()) {}

PlaceOrder::~PlaceOrder() {
    clearOrder();
    delete discountStrategy;
    delete currentState;
}

void PlaceOrder::addPizza(Pizza* pizza) { 
    pizzas.push_back(pizza); 
}

void PlaceOrder::setDiscountStrategy(DiscountStrategy* strategy) {
    delete discountStrategy;
    discountStrategy = strategy;
}

double PlaceOrder::calculateTotal() {
    double total = 0;
    for (auto pizza : pizzas) {
        total += pizza->getPrice();
    }
    return discountStrategy->applyDiscount(total);
}

int PlaceOrder::getPizzaCount() { 
    return pizzas.size(); 
}

double PlaceOrder::getTotal() { 
    return calculateTotal(); 
}

void PlaceOrder::processOrder() {
    currentState->handleState(this);
}

void PlaceOrder::setState(OrderPhase* newState) {
    if (currentState != nullptr) {
        delete currentState;
    }
    currentState = newState;
    std::cout << "Order state changed to: " << currentState->getStateName() << std::endl;
}

std::string PlaceOrder::getStatus() const {
    return currentState->getStateName();
}

void PlaceOrder::printOrderSummary() {
    std::cout << "\n=== Order Summary ===\n";
    std::cout << "Number of pizzas: " << getPizzaCount() << std::endl;
    std::cout << "Total cost: R" << getTotal() << std::endl;
    std::cout << "Discount applied: " << discountStrategy->getStrategyName() << std::endl;
    std::cout << "Current status: " << getStatus() << std::endl;
    
    if (!pizzas.empty()) {
        std::cout << "\nPizzas in order:\n";
        for (size_t i = 0; i < pizzas.size(); i++) {
            std::cout << (i + 1) << ". " << pizzas[i]->getName() << " - R" << pizzas[i]->getPrice() << std::endl;
        }
    }
}

void PlaceOrder::clearOrder() {
    for (auto pizza : pizzas) {
        delete pizza;
    }
    pizzas.clear();
    setDiscountStrategy(new RegularPrice());
    setState(new OrderStarted());
}

// ==================== PIZZA FACTORY IMPLEMENTATION ====================
Pizza* PizzaFactory::createPepperoniPizza() {
    ToppingGroup* pepperoni = new ToppingGroup("Pepperoni Pizza");
    pepperoni->add(new Topping(10.00, "Dough"));
    pepperoni->add(new Topping(5.00, "Tomato Sauce"));
    pepperoni->add(new Topping(15.00, "Cheese"));
    pepperoni->add(new Topping(20.00, "Pepperoni"));
    return new BasePizza(pepperoni);
}

Pizza* PizzaFactory::createVegetarianPizza() {
    ToppingGroup* vegetarian = new ToppingGroup("Vegetarian Pizza");
    vegetarian->add(new Topping(10.00, "Dough"));
    vegetarian->add(new Topping(5.00, "Tomato Sauce"));
    vegetarian->add(new Topping(15.00, "Cheese"));
    vegetarian->add(new Topping(12.00, "Mushrooms"));
    vegetarian->add(new Topping(10.00, "Green Peppers"));
    vegetarian->add(new Topping(8.00, "Onions"));
    return new BasePizza(vegetarian);
}

Pizza* PizzaFactory::createMeatLoversPizza() {
    ToppingGroup* meatLovers = new ToppingGroup("Meat Lovers Pizza");
    meatLovers->add(new Topping(10.00, "Dough"));
    meatLovers->add(new Topping(5.00, "Tomato Sauce"));
    meatLovers->add(new Topping(15.00, "Cheese"));
    meatLovers->add(new Topping(20.00, "Pepperoni"));
    meatLovers->add(new Topping(25.00, "Beef Sausage"));
    meatLovers->add(new Topping(22.00, "Salami"));
    return new BasePizza(meatLovers);
}

Pizza* PizzaFactory::createVegetarianDeluxePizza() {
    ToppingGroup* vegDeluxe = new ToppingGroup("Vegetarian Deluxe Pizza");
    vegDeluxe->add(new Topping(10.00, "Dough"));
    vegDeluxe->add(new Topping(5.00, "Tomato Sauce"));
    vegDeluxe->add(new Topping(15.00, "Cheese"));
    vegDeluxe->add(new Topping(12.00, "Mushrooms"));
    vegDeluxe->add(new Topping(10.00, "Green Peppers"));
    vegDeluxe->add(new Topping(8.00, "Onions"));
    vegDeluxe->add(new Topping(18.00, "Feta Cheese"));
    vegDeluxe->add(new Topping(15.00, "Olives"));
    return new BasePizza(vegDeluxe);
}

Pizza* PizzaFactory::addExtraCheese(Pizza* pizza) {
    return new ExtraCheese(pizza);
}

Pizza* PizzaFactory::addStuffedCrust(Pizza* pizza) {
    return new StuffedCrust(pizza);
}
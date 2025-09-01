#include "PizzaShop.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

void testCompositePattern() {
    std::cout << "\n=== Testing Composite Pattern ===\n";
    
    // Test individual toppings
    Topping* dough = new Topping(10.00, "Dough");
    Topping* sauce = new Topping(5.00, "Tomato Sauce");
    Topping* cheese = new Topping(15.00, "Cheese");
    Topping* pepperoni = new Topping(20.00, "Pepperoni");
    
    std::cout << "Individual toppings:\n";
    std::cout << dough->getName() << ": R" << dough->getPrice() << std::endl;
    std::cout << sauce->getName() << ": R" << sauce->getPrice() << std::endl;
    std::cout << cheese->getName() << ": R" << cheese->getPrice() << std::endl;
    std::cout << pepperoni->getName() << ": R" << pepperoni->getPrice() << std::endl;
    
    // Test topping group
    ToppingGroup* pizza = new ToppingGroup("Custom Pizza");
    pizza->add(dough);
    pizza->add(sauce);
    pizza->add(cheese);
    pizza->add(pepperoni);
    
    std::cout << "\nCustom pizza: " << pizza->getName() << std::endl;
    std::cout << "Total price: R" << pizza->getPrice() << std::endl;
    
    delete pizza; // This will delete all toppings as well
}

void testDecoratorPattern() {
    std::cout << "\n=== Testing Decorator Pattern ===\n";
    
    // Create a base pizza
    ToppingGroup* base = new ToppingGroup("Base Pizza");
    base->add(new Topping(10.00, "Dough"));
    base->add(new Topping(5.00, "Tomato Sauce"));
    base->add(new Topping(15.00, "Cheese"));
    
    BasePizza* pizza = new BasePizza(base);
    std::cout << "Base pizza: " << pizza->getName() << " - R" << pizza->getPrice() << std::endl;
    
    // Add extra cheese
    Pizza* withCheese = new ExtraCheese(pizza);
    std::cout << "With extra cheese: " << withCheese->getName() << " - R" << withCheese->getPrice() << std::endl;
    
    // Add stuffed crust
    Pizza* withCrust = new StuffedCrust(withCheese);
    std::cout << "With stuffed crust: " << withCrust->getName() << " - R" << withCrust->getPrice() << std::endl;
    
    delete withCrust; // This will delete all decorators and the base pizza
}

void testStrategyPattern() {
    std::cout << "\n=== Testing Strategy Pattern ===\n";
    
    // Create a test order
    PlaceOrder order;
    
    // Add some pizzas
    ToppingGroup* pizza1 = new ToppingGroup("Test Pizza 1");
    pizza1->add(new Topping(10.00, "Dough"));
    pizza1->add(new Topping(5.00, "Tomato Sauce"));
    pizza1->add(new Topping(15.00, "Cheese"));
    
    ToppingGroup* pizza2 = new ToppingGroup("Test Pizza 2");
    pizza2->add(new Topping(10.00, "Dough"));
    pizza2->add(new Topping(5.00, "Tomato Sauce"));
    pizza2->add(new Topping(15.00, "Cheese"));
    pizza2->add(new Topping(20.00, "Pepperoni"));
    
    order.addPizza(new BasePizza(pizza1));
    order.addPizza(new BasePizza(pizza2));
    
    // Test different strategies
    std::cout << "Order total with regular price: R" << order.calculateTotal() << std::endl;
    
    order.setDiscountStrategy(new BulkDiscount());
    std::cout << "Order total with bulk discount: R" << order.calculateTotal() << std::endl;
    
    order.setDiscountStrategy(new FamilyDiscount());
    std::cout << "Order total with family discount: R" << order.calculateTotal() << std::endl;
    
    // Test order summary
    order.printOrderSummary();
}

void testStatePattern() {
    std::cout << "\n=== Testing State Pattern ===\n";
    
    PlaceOrder order;
    
    // Add a test pizza
    ToppingGroup* pizza = new ToppingGroup("Test Pizza");
    pizza->add(new Topping(10.00, "Dough"));
    pizza->add(new Topping(5.00, "Tomato Sauce"));
    pizza->add(new Topping(15.00, "Cheese"));
    
    order.addPizza(new BasePizza(pizza));
    
    // Process through states
    std::cout << "Initial state: " << order.getStatus() << std::endl;
    
    for (int i = 0; i < 5 && order.getStatus() != "READY"; i++) {
        order.processOrder();
        std::cout << "State after processing: " << order.getStatus() << std::endl;
    }
    
    // Print final order summary
    order.printOrderSummary();
}

void testObserverPattern() {
    std::cout << "\n=== Testing Observer Pattern ===\n";
    
    // Create customers and website on the stack (not heap)
    Customer customer1("Alice");
    Customer customer2("Bob");
    Website website;
    
    PizzaMenu menu;
    menu.addObserver(&customer1);
    menu.addObserver(&customer2);
    menu.addObserver(&website);
    
    // Add a pizza to trigger notifications
    ToppingGroup* pizza = new ToppingGroup("Test Observer Pizza");
    pizza->add(new Topping(10.00, "Dough"));
    pizza->add(new Topping(5.00, "Tomato Sauce"));
    pizza->add(new Topping(15.00, "Cheese"));
    
    std::cout << "Adding pizza to menu (should trigger notifications):\n";
    BasePizza* basePizza = new BasePizza(pizza);
    menu.addPizza(basePizza);
    
    // Clean up the pizza we added
    delete basePizza;
}

void testPizzaFactory() {
    std::cout << "\n=== Testing Pizza Factory ===\n";
    
    // Test all factory methods
    Pizza* pepperoni = PizzaFactory::createPepperoniPizza();
    std::cout << "Pepperoni: " << pepperoni->getName() << " - R" << pepperoni->getPrice() << std::endl;
    
    Pizza* vegetarian = PizzaFactory::createVegetarianPizza();
    std::cout << "Vegetarian: " << vegetarian->getName() << " - R" << vegetarian->getPrice() << std::endl;
    
    Pizza* meatLovers = PizzaFactory::createMeatLoversPizza();
    std::cout << "Meat Lovers: " << meatLovers->getName() << " - R" << meatLovers->getPrice() << std::endl;
    
    Pizza* vegDeluxe = PizzaFactory::createVegetarianDeluxePizza();
    std::cout << "Vegetarian Deluxe: " << vegDeluxe->getName() << " - R" << vegDeluxe->getPrice() << std::endl;
    
    // Test decorator combinations
    Pizza* cheesePepperoni = PizzaFactory::addExtraCheese(PizzaFactory::createPepperoniPizza());
    std::cout << "Cheese Pepperoni: " << cheesePepperoni->getName() << " - R" << cheesePepperoni->getPrice() << std::endl;
    
    Pizza* stuffedMeatLovers = PizzaFactory::addStuffedCrust(PizzaFactory::createMeatLoversPizza());
    std::cout << "Stuffed Meat Lovers: " << stuffedMeatLovers->getName() << " - R" << stuffedMeatLovers->getPrice() << std::endl;
    
    // Cleanup
    delete pepperoni;
    delete vegetarian;
    delete meatLovers;
    delete vegDeluxe;
    delete cheesePepperoni;
    delete stuffedMeatLovers;
}

void testOrderProcessing() {
    std::cout << "\n=== Testing Complete Order Processing ===\n";
    
    // Create customers on stack
    Customer john("John");
    Customer sarah("Sarah");
    
    // Create menus and add observers
    PizzaMenu pizzaMenu;
    pizzaMenu.addObserver(&john);
    pizzaMenu.addObserver(&sarah);
    
    SpecialsMenu specialsMenu;
    specialsMenu.addObserver(&john);
    specialsMenu.addObserver(&sarah);
    
    // Create some pizzas for the menu
    Pizza* pepperoni = PizzaFactory::createPepperoniPizza();
    Pizza* vegetarian = PizzaFactory::createVegetarianPizza();
    Pizza* meatLovers = PizzaFactory::createMeatLoversPizza();
    Pizza* vegDeluxe = PizzaFactory::createVegetarianDeluxePizza();
    
    // Add pizzas to menu (this will notify observers)
    pizzaMenu.addPizza(pepperoni);
    pizzaMenu.addPizza(vegetarian);
    pizzaMenu.addPizza(meatLovers);
    pizzaMenu.addPizza(vegDeluxe);
    
    // Create a customer order
    PlaceOrder order;
    
    // Add pizzas to order
    order.addPizza(PizzaFactory::createPepperoniPizza());
    order.addPizza(PizzaFactory::createVegetarianPizza());
    order.addPizza(PizzaFactory::addExtraCheese(PizzaFactory::createMeatLoversPizza()));
    order.addPizza(PizzaFactory::addStuffedCrust(PizzaFactory::createVegetarianDeluxePizza()));
    
    // Apply discount based on order size
    if (order.getPizzaCount() >= 5) {
        order.setDiscountStrategy(new BulkDiscount());
        std::cout << "Applied bulk discount (10% off)\n";
    } else {
        order.setDiscountStrategy(new RegularPrice());
        std::cout << "Applied regular price\n";
    }
    
    // Process the order through states
    std::cout << "\nOrder processing:\n";
    int maxSteps = 10;
    int step = 0;
    
    while (order.getStatus() != "READY" && step < maxSteps) {
        std::cout << "Step " << step + 1 << ": ";
        order.processOrder();
        step++;
    }
    
    // Show final order details
    order.printOrderSummary();
    
    // Test clearing the order
    std::cout << "\nTesting order clearance:\n";
    order.clearOrder();
    std::cout << "After clearing - Pizzas: " << order.getPizzaCount() << ", Total: R" << order.getTotal() << std::endl;
    
    // Clean up menu pizzas
    delete pepperoni;
    delete vegetarian;
    delete meatLovers;
    delete vegDeluxe;
}

void testEdgeCases() {
    std::cout << "\n=== Testing Edge Cases ===\n";
    
    // Test empty order
    PlaceOrder emptyOrder;
    std::cout << "Empty order total: R" << emptyOrder.calculateTotal() << std::endl;
    emptyOrder.printOrderSummary();
    
    // Test single pizza order
    PlaceOrder singleOrder;
    singleOrder.addPizza(PizzaFactory::createPepperoniPizza());
    std::cout << "Single pizza order total: R" << singleOrder.calculateTotal() << std::endl;
    singleOrder.printOrderSummary();
    
    // Test bulk discount threshold (5 pizzas)
    PlaceOrder bulkOrder;
    for (int i = 0; i < 5; i++) {
        bulkOrder.addPizza(PizzaFactory::createPepperoniPizza());
    }
    bulkOrder.setDiscountStrategy(new BulkDiscount());
    std::cout << "5 pizza order with bulk discount: R" << bulkOrder.calculateTotal() << std::endl;
    bulkOrder.printOrderSummary();
    
    // Test order state with no pizzas
    PlaceOrder emptyStateOrder;
    std::cout << "Empty order state: " << emptyStateOrder.getStatus() << std::endl;
    emptyStateOrder.processOrder();
    std::cout << "Empty order state after processing: " << emptyStateOrder.getStatus() << std::endl;
}

void testDecoratorPrintMethods() {
    std::cout << "\n=== Testing Decorator Print Methods ===\n";
    
    Pizza* base = PizzaFactory::createPepperoniPizza();
    
    ExtraCheese* withCheese = new ExtraCheese(base);
    std::cout << "Testing ExtraCheese printPizza():\n";
    withCheese->printPizza();
    
    StuffedCrust* withCrust = new StuffedCrust(PizzaFactory::createVegetarianPizza());
    std::cout << "Testing StuffedCrust printPizza():\n";
    withCrust->printPizza();
    
    delete withCheese;
    delete withCrust;
}

void testObserverRemoval() {
    std::cout << "\n=== Testing Observer Removal ===\n";
    
    Customer alice("Alice");
    Customer bob("Bob");
    Website website;
    
    PizzaMenu menu;
    menu.addObserver(&alice);
    menu.addObserver(&bob);
    menu.addObserver(&website);
    
    std::cout << "Adding pizza with all observers:\n";
    menu.addPizza(PizzaFactory::createPepperoniPizza());
    
    std::cout << "\nRemoving Alice as observer:\n";
    menu.removeObserver(&alice);
    
    std::cout << "Adding another pizza (Alice shouldn't be notified):\n";
    menu.addPizza(PizzaFactory::createVegetarianPizza());
    
    // Clean up - note: the pizzas added to menu aren't automatically deleted
    // so we need to be careful about memory management here
}
void testPreparingToPendingTransition() {
    std::cout << "\n=== Testing Specific Preparing->Pending Transition ===\n";
    
    PlaceOrder order;
    
    // Add a test pizza
    ToppingGroup* pizza = new ToppingGroup("Test Pizza");
    pizza->add(new Topping(10.00, "Dough"));
    pizza->add(new Topping(5.00, "Tomato Sauce"));
    pizza->add(new Topping(15.00, "Cheese"));
    order.addPizza(new BasePizza(pizza));
    
    // Manually set to Preparing state
    order.setState(new Preparing());
    std::cout << "Set initial state to: " << order.getStatus() << std::endl;
    
    // Process and hope for a backward transition
    int attempts = 0;
    while (attempts < 10) {
        std::string previousState = order.getStatus();
        order.processOrder();
        std::string currentState = order.getStatus();
        
        std::cout << "Attempt " << attempts + 1 << ": ";
        std::cout << previousState << " -> " << currentState;
        
        if (previousState == "PREPARING" && currentState == "PENDING") {
            std::cout << " ✅ SUCCESS: Backward transition demonstrated!";
            std::cout << std::endl;
            break;
        }
        std::cout << std::endl;
        
        // Reset to Preparing if we went to READY
        if (currentState == "READY") {
            order.setState(new Preparing());
            std::cout << "Reset to PREPARING for next attempt..." << std::endl;
        }
        
        attempts++;
    }
    
    if (attempts >= 10) {
        std::cout << "Could not demonstrate backward transition after 10 attempts.\n";
        std::cout << "The random probability might need adjustment for testing.\n";
    }
}

void testMenuPizzaRemoval() {
    std::cout << "\n=== Testing Menu Pizza Removal ===\n";
    
    Customer customer("TestCustomer");
    PizzaMenu pizzaMenu;
    SpecialsMenu specialsMenu;
    
    pizzaMenu.addObserver(&customer);
    specialsMenu.addObserver(&customer);
    
    Pizza* pizza1 = PizzaFactory::createPepperoniPizza();
    Pizza* pizza2 = PizzaFactory::createVegetarianPizza();
    
    std::cout << "Adding pizzas to menus:\n";
    pizzaMenu.addPizza(pizza1);
    specialsMenu.addPizza(pizza2);
    
    std::cout << "\nRemoving pizzas from menus:\n";
    pizzaMenu.removePizza(pizza1);
    specialsMenu.removePizza(pizza2);
    
    delete pizza1;
    delete pizza2;
}

int main() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    
    std::cout << "=== Romeo's Pizza Shop Comprehensive Tests ===\n\n";
    
    testCompositePattern();
    testDecoratorPattern();
    testStrategyPattern();
    testStatePattern();
    testObserverPattern();
    testPizzaFactory();
    testOrderProcessing();
    testEdgeCases();

    //edge case
    testDecoratorPrintMethods();
    testObserverRemoval();              // NEW
    testMenuPizzaRemoval();             // NEW
    // state moving back
     testPreparingToPendingTransition();
    
    std::cout << "\n=== All tests completed successfully ===\n";
    
    return 0;
}
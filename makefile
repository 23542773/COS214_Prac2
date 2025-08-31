CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic -g --coverage
LDFLAGS = --coverage

TARGET = pizzaShop
OBJS = PizzaShop.o TestingMain.o

all: $(TARGET)

PizzaShop.o: PizzaShop.cpp PizzaShop.h
	$(CXX) $(CXXFLAGS) -c PizzaShop.cpp

TestingMain.o: TestingMain.cpp PizzaShop.h
	$(CXX) $(CXXFLAGS) -c TestingMain.cpp

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET) $(LDFLAGS)

run: $(TARGET)
	./$(TARGET)

# Generate coverage report
coverage: clean $(TARGET) run
	gcov -b PizzaShop.cpp TestingMain.cpp > coverage.txt
	@echo "Coverage report generated in coverage.txt"

clean:
	rm -rf *.o $(TARGET) *.gcda *.gcno *.gcov coverage.info coverage_report coverage.txt
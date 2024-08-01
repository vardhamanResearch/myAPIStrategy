#include <iostream>
#include <string>

// Enum to represent different states of the strategy
enum class StrategyState {
    INIT,
    ENTRY,
    EXIT,
    FINALIZE
};

// Abstract base class for a trading strategy
class TradingStrategy {
public:
    virtual void initialize() = 0;
    virtual void enter() = 0;
    virtual void exit() = 0;
    virtual void finalize() = 0;
    virtual ~TradingStrategy() = default;
};

// Concrete implementation of a trading strategy
class MyTradingStrategy : public TradingStrategy {
private:
    StrategyState currentState;
    
public:
    MyTradingStrategy() : currentState(StrategyState::INIT) {}

    void initialize() override {
        std::cout << "Initializing strategy...\n";
        // Initialization logic here
        currentState = StrategyState::ENTRY;
    }

    void enter() override {
        std::cout << "Entering the market...\n";
        // Entry logic here
        currentState = StrategyState::EXIT;
    }

    void exit() override {
        std::cout << "Exiting the market...\n";
        // Exit logic here
        currentState = StrategyState::FINALIZE;
    }

    void finalize() override {
        std::cout << "Finalizing strategy...\n";
        // Finalization logic here
    }

    void run() {
        switch (currentState) {
            case StrategyState::INIT:
                initialize();
                break;
            case StrategyState::ENTRY:
                enter();
                break;
            case StrategyState::EXIT:
                exit();
                break;
            case StrategyState::FINALIZE:
                finalize();
                break;
        }
    }
};

// Main function to execute the strategy
int main() {
    MyTradingStrategy strategy;
    
    // Run the strategy through its states
    strategy.run();  // INIT -> ENTRY
    strategy.run();  // ENTRY -> EXIT
    strategy.run();  // EXIT -> FINALIZE
    
    return 0;
}

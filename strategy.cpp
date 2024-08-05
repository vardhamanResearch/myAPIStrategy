//code will begin from here

#include<bits/stdc++.h>
#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <chrono>
// #include <nlohmann/json.hpp>

using namespace std;
// using json = nlohmann::json;

// Structure to hold option data,to be changed to enum/union
struct OptionData {
    double strike;
    double price;
    double expiry;
    //other imp data
};

// Class to manage the Butterfly Strategy
class CallButterflyStrategy{
public:
    CallButterflyStrategy(string& symbol, double maxDebit, double takeProfit, double stopLoss , double strikediff)
        : symbol(symbol), maxDebit(maxDebit), takeProfit(takeProfit), stopLoss(stopLoss), strikediff(strikediff) {}

    void executeStrategy() {
        vector<OptionData> options = fetchOptionsData(symbol);

        // For simplicity, assume options are sorted by strike price
        double atmStrike = options[options.size() / 2].strike;
        OptionData lowerStrikeCall, middleStrikeCall, upperStrikeCall;

        for (auto& option : options) {
            if (option.strike == atmStrike - strikediff) {
                lowerStrikeCall = option;
            } else if (option.strike == atmStrike) {
                middleStrikeCall = option;
            } else if (option.strike == atmStrike + strikediff) {
                upperStrikeCall = option;
            }
        }
                        // ask +ask - 2*bid
        double debit = lowerStrikeCall.price + upperStrikeCall.price - 2 * middleStrikeCall.price;
        if (debit <= maxDebit) {
            // Place trades 
            //integrate with api
            cout << "Buying 1 call at strike " << lowerStrikeCall.strike << " for price " << lowerStrikeCall.price << endl;
            cout << "Selling 2 calls at strike " << middleStrikeCall.strike << " for price " << middleStrikeCall.price << endl;
            cout << "Buying 1 call at strike " << upperStrikeCall.strike << " for price " << upperStrikeCall.price << endl;
            monitorTrade(lowerStrikeCall, middleStrikeCall, upperStrikeCall);
        }
    }

private:
    string symbol;
    double maxDebit;
    double takeProfit;
    double stopLoss;
    double strikediff;

    vector<OptionData> fetchOptionsData(string& symbol){
        //get the data from api
    }

    void monitorTrade(OptionData lowerStrikeCall, OptionData middleStrikeCall, OptionData upperStrikeCall) {
        bool tradeActive = true;
        while (tradeActive) {
            vector<OptionData> options = fetchOptionsData(symbol);

            // Update option prices
            for (auto& option : options) {
                if (option.strike == lowerStrikeCall.strike) {
                    lowerStrikeCall.price = option.price;
                } else if (option.strike == middleStrikeCall.strike) {
                    middleStrikeCall.price = option.price;
                } else if (option.strike == upperStrikeCall.strike) {
                    upperStrikeCall.price = option.price;
                }
            }

            double currentValue = lowerStrikeCall.price + upperStrikeCall.price - 2 * middleStrikeCall.price;
            if (currentValue >= takeProfit) {
                cout << "Exiting trade with profit. Current value: " << currentValue << endl;
                // Exit trades 
                //api integration
                tradeActive = false;
            } else if (currentValue <= stopLoss) {
                cout << "Exiting trade with stop loss. Current value: " << currentValue << endl;
                // Exit trades 
                // api integration
                tradeActive = false;
            }

            this_thread::sleep_for(chrono::seconds(1)); // Short sleep to prevent overloading the API
        }
    }
};

int main() {
    string symbol = "NIFTY"; 
    double maxDebit = 20; 
    double takeProfit = 50; 
    double stopLoss = 10; 
    double strikediff = 100;

    CallButterflyStrategy strategy(symbol, maxDebit, takeProfit, stopLoss , strikediff);
    strategy.executeStrategy();

    return 0;
}

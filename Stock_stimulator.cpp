#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <map>

using namespace std;

class Stock {
public:
    string name;
    float price;

    Stock(string name, float price) {
        this->name = name;
        this->price = price;
    }

    void updatePrice() {
        float change = (rand() % 200 - 100) / 10.0; // -10% to +10%
        price += price * (change / 100);
        if (price < 1) price = 1;
    }
};

class Portfolio {
public:
    map<string, int> ownedStocks;
    float balance;

    Portfolio(float startBalance = 10000) {
        balance = startBalance;
    }

    void buyStock(Stock &stock, int quantity) {
        float cost = stock.price * quantity;
        if (cost > balance) {
            cout << "Insufficient balance!" << endl;
        } else {
            balance -= cost;
            ownedStocks[stock.name] += quantity;
            cout << "Bought " << quantity << " of " << stock.name << endl;
        }
    }

    void sellStock(Stock &stock, int quantity) {
        if (ownedStocks[stock.name] < quantity) {
            cout << "You don't own that many shares!" << endl;
        } else {
            balance += stock.price * quantity;
            ownedStocks[stock.name] -= quantity;
            cout << "Sold " << quantity << " of " << stock.name << endl;
        }
    }

    void viewPortfolio(const vector<Stock> &market) {
        cout << "\n--- Portfolio ---\n";
        cout << fixed << setprecision(2);
        cout << "Balance: $" << balance << endl;
        float totalValue = balance;
        for (auto &s : market) {
            if (ownedStocks[s.name] > 0) {
                float value = s.price * ownedStocks[s.name];
                cout << s.name << ": " << ownedStocks[s.name] << " shares @ $" << s.price << " = $" << value << endl;
                totalValue += value;
            }
        }
        cout << "Total Net Worth: $" << totalValue << endl;
    }
};

void showMarket(vector<Stock> &stocks) {
    cout << "\n--- Stock Market ---\n";
    cout << fixed << setprecision(2);
    for (int i = 0; i < stocks.size(); i++) {
        cout << i + 1 << ". " << stocks[i].name << " - $" << stocks[i].price << endl;
    }
}

void updateMarket(vector<Stock> &stocks) {
    for (auto &stock : stocks)
        stock.updatePrice();
    cout << "Market updated!" << endl;
}

int main() {
    srand(time(0));
    vector<Stock> market = {
        Stock("Google", 1200.0),
        Stock("Apple", 800.0),
        Stock("Amazon", 950.0),
        Stock("Tesla", 600.0)
    };

    Portfolio user;

    int choice;
    while (true) {
        cout << "\n1. View Market\n2. Buy Stock\n3. Sell Stock\n4. View Portfolio\n5. Update Prices\n6. Exit\nChoice: ";
        cin >> choice;

        if (choice == 1) {
            showMarket(market);
        } else if (choice == 2) {
            showMarket(market);
            int id, qty;
            cout << "Enter stock number to buy: ";
            cin >> id;
            cout << "Enter quantity: ";
            cin >> qty;
            if (id > 0 && id <= market.size()) {
                user.buyStock(market[id - 1], qty);
            }
        } else if (choice == 3) {
            showMarket(market);
            int id, qty;
            cout << "Enter stock number to sell: ";
            cin >> id;
            cout << "Enter quantity: ";
            cin >> qty;
            if (id > 0 && id <= market.size()) {
                user.sellStock(market[id - 1], qty);
            }
        } else if (choice == 4) {
            user.viewPortfolio(market);
        } else if (choice == 5) {
            updateMarket(market);
        } else if (choice == 6) {
            break;
        } else {
            cout << "Invalid option!" << endl;
        }
    }

    return 0;
}

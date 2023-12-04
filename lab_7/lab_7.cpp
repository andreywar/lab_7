#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

struct PhotoOrder {
    string masterName;
    string photoType;
    string paperType;
    int quantity;
    double price;
};

bool comparePhotoType(const PhotoOrder& a, const PhotoOrder& b) {
    return a.photoType < b.photoType;
}

int main() {
    ifstream file("orders.txt");
    if (!file.is_open()) {
        cout << "Error opening file" << endl;
        return 1;
    }

    vector<PhotoOrder> orders;
    string masterName, photoType, paperType, quantityStr, priceStr;
    int quantity;
    double price;

    while (file >> masterName >> photoType >> paperType >> quantityStr >> priceStr) {
        quantity = stoi(quantityStr);
        price = stod(priceStr);
        orders.push_back({ masterName, photoType, paperType, quantity, price });
    }

    file.close();

    sort(orders.begin(), orders.end(), comparePhotoType);

    cout << "Master Name   | Photo Type | Paper Type | Quantity | Price" << endl;
    cout << "---------------------------------------------------------------" << endl;

    string currentPhotoType = orders[0].photoType;
    double sum = 0;
    int maxOrderCount = 0;
    string popularMaster;

    for (const auto& order : orders) {
        if (order.photoType != currentPhotoType) {
            cout << "Total: " << sum << endl;
            currentPhotoType = order.photoType;
            sum = 0;
        }
        sum += order.price * order.quantity;
        if (order.quantity > maxOrderCount) {
            maxOrderCount = order.quantity;
            popularMaster = order.masterName;
        }
        cout << order.masterName << " | " << order.photoType << " | " << order.paperType << " | "
            << order.quantity << " | " << order.price * order.quantity << endl;
    }
    cout << "Total: " << sum << endl;

    ofstream outFile("results.txt");
    outFile << "Master Name   | Photo Type | Paper Type | Quantity | Price" << endl;
    outFile << "---------------------------------------------------------------" << endl;

    for (const auto& order : orders) {
        outFile << order.masterName << " | " << order.photoType << " | " << order.paperType << " | "
            << order.quantity << " | " << order.price * order.quantity << endl;
    }
    outFile << "Total: " << sum << endl;
    outFile << "Most popular paper type: " << maxOrderCount << endl;
    outFile << "Most popular master: " << popularMaster << endl;

    outFile.close();

    return 0;
}
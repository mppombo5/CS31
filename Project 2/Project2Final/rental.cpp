#include <iostream>
#include <string>
using namespace std;

int main() {

    // we probably won't need to change these values for the project,
    // but if we had to this would make it easier.

    const double NON_LUXURY_RATE = 33;
    const double LUXURY_RATE = 61;
    const double FIRST_100 = 0.27;
    const double AFTER_400 = 0.19;
    const double NEXT_300 = 0.21;
    const double NEXT_300_WINTER = 0.27;

    // gather the input and assign to variables

    cout << "Odometer at start: ";
    int odoStart;
    cin >> odoStart;

    cout << "Odometer at end: ";
    int odoEnd;
    cin >> odoEnd;

    cout << "Rental days: ";
    int rentalDays;
    cin >> rentalDays;

    cin.ignore(100000, '\n');

    cout << "Customer name: ";
    string customerName;
    getline(cin, customerName);

    cout << "Luxury car? (y/n): ";
    string luxuryString;
    getline (cin, luxuryString);

    cout << "Month (1=Jan, 2=Feb, etc): ";
    int month;
    cin >> month;

    cout << "---" << endl;

    // check if the inputs are incorrect, and respond according to the specs

    if (odoStart < 0) {
        cout << "The starting odometer reading must be nonnegative.";
        return 1;
    }
    if (odoEnd < odoStart) {
        cout << "The final odometer reading must be at least as large as the starting reading.";
        return 1;
    }
    if (rentalDays < 0) {
        cout << "The number of rental days must be positive.";
        return 1;
    }
    if (customerName.empty()) {
        cout << "You must enter a customer name.";
        return 1;
    }
    if (!(luxuryString == "y" || luxuryString == "n")) {
        cout << "You must enter y or n.";
        return 1;
    }
    if (month < 1 || month > 12) {
        cout << "The month number must be in the range 1 through 12.";
        return 1;
    }

    // declare variables for miles traveled, cost due to miles driven,
    // cost due to luxury/basic, and cost for middle 300 winter/non-winter

    int totalMiles = (odoEnd - odoStart);
    double mileCost;
    double luxuryCost;
    double next300;

    // check if the car is luxury or not

    if (luxuryString == "y") {
        luxuryCost = (LUXURY_RATE * rentalDays);
    }
    else if (luxuryString == "n") {
        luxuryCost = (NON_LUXURY_RATE * rentalDays);
    }

    // if it's rented during a winter month, set the cost equal
    // to the winter constant; otherwise, set it to the non-winter constant

    if (month == 12 || month <= 3){
        next300 = NEXT_300_WINTER;
    }
    else {
        next300 = NEXT_300;
    }

    // check how many miles were driven, and calculate the cost accordingly

    if (totalMiles <= 100) {
        mileCost = (totalMiles * FIRST_100);
    }
    else if (totalMiles <= 400) {
            mileCost = ((100 * FIRST_100) + ((totalMiles - 100) * next300));
    }
    else if (totalMiles > 400) {
            mileCost = ((100 * FIRST_100) + (300 * next300) + ((totalMiles - 400) * AFTER_400));
    }

    cout.setf(ios::fixed);
    cout.precision(2);

    cout << "The rental charge for " << customerName << " is $" << (luxuryCost + mileCost) << endl;

    return 0;
}
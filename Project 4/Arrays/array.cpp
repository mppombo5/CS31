#include <iostream>
#include <string>
using namespace std;

int appendToAll(string a[], int n, string value);
int lookup(const string a[], int n, string target);
int positionOfMax(const string a[], int n);
int rotateLeft(string a[], int n, int pos);

int main() {

    string arr[9] = {
            "ape", "bonjour", "crapple", "heist", "georgia", "forgery", "alphabet", "denim", "icarus"
    };

    string s;
    cout << "What string would you like to add on? ";
    getline(cin, s);

    int n;
    cout << "Up to what position would you like to append this string? ";
    cin >> n;

    appendToAll(arr, n, s);

    for (int i = 0; i < 9; i++) {
        cout << arr[i] << endl;
    }

    return 0;
}

int appendToAll(string a[], int n, string value) {

    if (n < 0)
        return -1;

    for (int i = 0; i < n; i++) {
        a[i] += value;
    }

    return n;
}

int lookup(const string a[], int n, string target) {

    if (n <= 0)
        return -1;

    for (int i = 0; i < (n - 1); i++) {
        if (a[i] == target) {
            return i;
        }
    }
    return -1;
}

int positionOfMax(const string a[], int n) {

    if (n <= 0)
        return -1;

    int maxPos = 0;
    for (int i = 0; i < n; i++) {
        if (a[i] > a[maxPos])
            maxPos = i;
    }

    return (maxPos);
}

int rotateLeft(string a[], int n, int pos) {
    
}
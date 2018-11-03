#include <iostream>
#include <string>
using namespace std;

int appendToAll(string a[], int n, string value);
int lookup(const string a[], int n, string target);

int main() {

    string arr[9] = {
            "hey there", "hi", "hello", "howdy", "hola", "bonjour", "asdf", "bcde", "thicc thighs"
    };

    string s;
    cout << "What string would you like to look for? ";
    getline(cin, s);

    int n;
    cout << "Up to which position would you like to check? ";
    cin >> n;

    int pos = lookup(arr, n, s);

    cout << '"' << s << '"' << " is in position " << pos << ", starting from 0." << endl;

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

    if (n < 0)
        return -1;

    for (int i = 0; i <= n; i++) {
        if (a[i] == target) {
            return i;
        }
    }
    return -1;
}
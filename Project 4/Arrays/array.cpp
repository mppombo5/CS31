#include <iostream>
#include <string>
using namespace std;

int appendToAll(string a[], int n, string value);
int lookup(const string a[], int n, string target);
int positionOfMax(const string a[], int n);
int rotateLeft(string a[], int n, int pos);
int countRuns(const string a[], int n);
int flip(string a[], int n);
int differ(const string a1[], int n1, const string a2[], int n2);
int subsequence(const string a1[], int n1, const string a2[], int n2);
int lookupAny(const string a1[], int n1, const string a2[], int n2);
int divide(string a[], int n, string divider);

int main() {

    string arr[9] = {
            "ape", "bonjour", "crapple", "heist", "georgia", "forgery", "effervescent", "denim", "icarus"
    };

    string arr2[9] = {
            "ape", "bonjour", "crapple", "crapple", "georgia", "forgery", "effervescent", "denim", "icarus"
    };

    int n;
    cout << "Up to which position would you like to check for runs? ";
    cin >> n;

    int p = countRuns(arr2, n);

    cout << "countRuns returns " << p << ".\n";

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

    for (int i = 0; i < (n - 1); i++) {
        if (a[i] == target) {
            return i;
        }
    }
    return -1;
}

int positionOfMax(const string a[], int n) {

    if (n < 0)
        return -1;

    int maxPos = 0;
    for (int i = 0; i < n; i++) {
        if (a[i] > a[maxPos])
            maxPos = i;
    }

    return maxPos;
}

// put word at pos at position n, move other letters to the left
int rotateLeft(string a[], int n, int pos) {

    if (pos < 0)
        return -1;

    // create separate string so you can smack it on the end;
    // removes need for extra array
    string s = a[pos];
    for (int i = pos; i < (n-1); i++) {
        a[i] = a[i+1];
    }
    a[n-1] = s;
    return pos;
}

int countRuns(const string a[], int n) {

    if (n < 0)
        return -1;

    int i = 1;
    int runsCounter = 0;
    while (i <= n) {
        // don't add to counter until you hit a new word
        while (a[i-1] == a[i]) {
            i++;
        }
        runsCounter++;
        i++;
    }

    return runsCounter;
}

int flip(string a[], int n) {

    if (n < 0)
        return -1;


    for (int i = 0; i < (n / 2); i++) {
        // create separate string so it's not overwritten by a[i]
        string last = a[n-(i+1)];
        // don't use last, it'll reassign the value before the last replacement
        a[n-(i+1)] = a[i];
        a[i] = last;
    }
    return n;
}

int differ(const string a1[], int n1, const string a2[], int n2) {

    if (n1 < 0 || n2 < 0)
        return -1;

    int l;
    if (n1 <= n2) {
        l = n1;
    }
    else if (n2 < n1) {
        l = n2;
    }

    for (int i = 0; i < l; i++) {
        if (a1[i] != a2[i]) {
            // makes it easier to check when it actually finds a different string rather than
            // defaulting to l
            cerr << "a different string was found at position " << i << ".\n";
            return i;
        }
    }
    return l;
}

int subsequence(const string a1[], int n1, const string a2[], int n2) {

}

int lookupAny(const string a1[], int n1, const string a2[], int n2) {

}

int divide(string a[], int n, string divider) {

}
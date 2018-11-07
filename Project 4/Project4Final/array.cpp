#include <iostream>
#include <string>
#include <cassert>
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

    string h[7] = { "greg", "gavin", "ed", "xavier", "", "eleni", "fiona" };
    string h1[7] = { "greg", "gavin", "ed", "fiona", "", "eleni", "xavier" };
    assert(lookup(h, 7, "eleni") == 5);
    assert(lookup(h, 7, "ed") == 2);
    assert(lookup(h, 2, "ed") == -1);
    assert(positionOfMax(h, 7) == 3);

    // mine
    assert(lookup(h, 7, "fiona") == 6);
    assert(positionOfMax(h1, 7) == 6);

    string g[4] = { "greg", "gavin", "fiona", "kevin" };
    assert(differ(h, 4, g, 4) == 2);

    //mine
    assert(differ(h, 7, h1, 7) == 3);

    assert(appendToAll(g, 4, "?") == 4 && g[0] == "greg?" && g[3] == "kevin?");
    //assert(rotateLeft(g, 4, 1) == 1 && g[1] == "fiona?" && g[3] == "gavin?");

    string e[4] = { "ed", "fiona", "", "xavier" };
    string e1[4] = { "fiona", "", "eleni", "xavier" };
    assert(subsequence(h, 7, e, 4) == -1);

    //mine
    assert(subsequence(h1, 7, e1, 4) == 3);

    string d[5] = { "gavin", "gavin", "gavin", "xavier", "eleni" };
    string d1[5] = { "gavin", "gavin", "gavin", "xavier", "xavier" };
    assert(countRuns(d, 5) == 3);

    //mine
    assert(countRuns(d1, 5) == 2);

    string f[3] = { "fiona", "ed", "john" };
    assert(lookupAny(h, 7, f, 3) == 2);
    assert(flip(f, 3) == 3 && f[0] == "john" && f[2] == "fiona");

    assert(divide(h, 7, "fiona") == 3);

    string arrO[9] = {
            "ape", "bonjour", "crapple", "denim", "effervescent", "forgery", "georgia", "heist", "icarus"
    };

    string arr[9] = {
            "ape", "bonjour", "crapple", "heist", "georgia", "forgery", "effervescent", "denim", "icarus"
    };

    string arr2[9] = {
            "forgery", "georgia", "heist", "icarus", "crapple", "ape", "bonjour", "denim", "effervescent"
    };
    string arr3[9] = {
            "ape", "bonjour", "crapple", "heist", "georgia", "forgery", "effervescent", "denim", "falsity"
    };

    assert(divide(arr2, 9, "z") == 9);
    assert(divide(arr2, 9, "crapple") == 2);
    assert(divide(arr2, 9, "denim") == 3);
    assert(divide(arr2, 9, "a") == 0);
    assert(divide(arr2, 9, "ape") == 0);
    assert(divide(arr2, 9, "icarus") == 8);

    assert(rotateLeft(arr, 9, 8) == 8);
    assert(rotateLeft(arr, 9, 9) == -1);

    assert(differ(arr, 9, arrO, 9) == 3);
    assert(differ(arr, 9, arr3, 9) == 8);

    cout << "All test cases succeeded!\n";

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

    for (int i = 0; i < n; i++) {
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

    if (pos < 0 || n < 0 || pos >= n)
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
        // added check for if i ≥ n, otherwise it'd check out of bounds
        while (i < n && a[i-1] == a[i]) {
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
        string latter = a[n-(i+1)];
        // don't use latter, it'll reassign the value before the last replacement
        a[n-(i+1)] = a[i];
        a[i] = latter;
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
            // cerr << "a different string was found at position " << i << ".\n";
            return i;
        }
    }
    return l;
}

int subsequence(const string a1[], int n1, const string a2[], int n2) {

    if (n1 < 0 || n2 < 0 || n2 > n1)
        return -1;

    if (n2 == 0)
        return -1;

    // i is the position of the string in a1, j is the position in a2
    int i = 0;
    int j = 0;
    while (i < n1) {
        if (a1[i] == a2[j]) {
            i++;
            j++;
        }
        else {
            i++;
            j = 0;
        }
        if (j == n2) {
            return (i - n2);
        }
    }
    return -1;
}

int lookupAny(const string a1[], int n1, const string a2[], int n2) {

    if (n1 < 0 || n2 < 0)
        return -1;

    for (int i = 0; i < n1; i++) {
        for (int j = 0; j < n2; j++) {
            if (a1[i] == a2[j]) {
                return i;
            }
        }
    }
    return -1;
}

int divide(string a[], int n, string divider) {

    if (n < 0)
        return -1;

    int i = 0;
    int j = (n - 1);

    // only go until they reach each other
    // this is basically the partition part of a quicksort
    while (i <= j) {
        // increment i until a[i] ≥ divider
        // also check if it's greater than n, because it'll go in an endless loop
        while (i < n && a[i] < divider) {
            i++;
        }
        // decrement j until a[j] < divider
        // also check if it's greater than n
        while (j >= 0 && a[j] >= divider)
            j--;
        // swap the two values only if i is still less than j
        if (i <= j) {
            string latter = a[j];
            a[j] = a[i];
            a[i] = latter;
            i++;
            j--;
        }
    }

    // dividerPos is the position of divider in the array, -1 if it's not in the array
    int dividerPos = -1;
    for (int k = 0; k < n; k++) {
        if (a[k] == divider) {
            dividerPos = k;
            break;
        }
    }

    // only do this if divider is contained in the array, that's why I set it to -1
    if (dividerPos != -1) {
        string tmp = a[dividerPos];
        a[dividerPos] = a[i];
        a[i] = tmp;
    }

    for (int k = 0; k < n; k++) {
        if (a[k] >= divider)
            return k;
    }
    return n;
}
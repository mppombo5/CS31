#include <iostream>
#include <cstring>
#include <cassert>
using namespace std;

const int MAX_WORD_LENGTH = 20;

void makeUppercase(char words[][MAX_WORD_LENGTH+1], int n);

void rotateLeftAll(char a1[][MAX_WORD_LENGTH+1], char a2[][MAX_WORD_LENGTH+1], int sep[], int n, int pos);

int makeProper(char word1[][MAX_WORD_LENGTH+1], char word2[][MAX_WORD_LENGTH+1],
               int separation[], int nPatterns);

int rate(const char document[], const char word1[][MAX_WORD_LENGTH+1],
         const char word2[][MAX_WORD_LENGTH+1], const int separation[], int nPatterns);

// nPatterns is the number of pairs of words in the arrays, could consider it the number in the first bracket
// therefore, nPatterns is the position of both words AND the separation value

int main() {

    char test1[6][MAX_WORD_LENGTH+1] = {
            {"HELLO"},
            {"THERE"},
            {"GENERAL"},
            {"KENOBI"},
            {"YOU"},
            {"ARE"}
    };
    char test2[6][MAX_WORD_LENGTH+1] = {
            {"A"},
            {"BOLD"},
            {"ONE"},
            {"YOURE"},
            {"SHORTER"},
            {"THAN"}
    };
    int testSep[6] = {
            1, 2, 3, 4, 5, 6
    };

    int m = makeProper(test1, test2, testSep, 6);

    for (int i = 0; i < m; i++) {
        for (int k = 0; test1[i][k] != '\0'; k++) {
            cout << test1[i][k];
        }
        cout << endl;
    }
    cout << endl;
    for (int i = 0; i < m; i++) {
        for (int k = 0; test2[i][k] != '\0'; k++) {
            cout << test2[i][k];
        }
        cout << endl;
    }
    cout << endl;
    for (int i = 0; i < m; i++) {
        cout << testSep[i];
        cout << endl;
    }

    return 0;
}

void makeUppercase(char words[][MAX_WORD_LENGTH+1], int n) {
    for (int i = 0; i < n; i++) {
        for (int k = 0; words[i][k] != '\0'; k++) {
            words[i][k] = (char) tolower(words[i][k]);
        }
    }
}

// use this function to remove the element at position pos and shift all other elements left
// pretty similar to rotateLeft from project 4
void rotateLeftAll(char a1[][MAX_WORD_LENGTH+1], char a2[][MAX_WORD_LENGTH+1], int sep[], int n, int pos) {

    for (int i = pos; i < (n-1); i++) {
        strcpy(a1[i], a1[i+1]);
        strcpy(a2[i], a2[i+1]);
        sep[i] = sep[i+1];
    }
}

// don't even need to make the words the right length apart, just make the list of words proper
// I was WAY overthinking this
// put the patterns in "proper form" according to the spec
int makeProper(char word1[][MAX_WORD_LENGTH+1], char word2[][MAX_WORD_LENGTH+1],
               int separation[], int nPatterns) {

    // no patterns, so the length of the array is 0
    if (nPatterns <= 0)
        return 0;

    // make new number r which starts as nPatterns, decrease it as you remove patterns
    int r = nPatterns;

    // make both string arrays uppercase to match requirements
    makeUppercase(word1, nPatterns);
    makeUppercase(word2, nPatterns);

    // check up to r, because the length of the array could change
    for (int i = 0; i < r; i++) {
        // first, remove all elements in the arrays for which the separation value is negative
        if (separation[i] < 0) {
            // move all elements in those three arrays left at position i all the way to r
            rotateLeftAll(word1, word2, separation, r, i);

            // decrease new number of patterns by 1
            r--;

            // decrease i so that it goes back over the same position, which now contains the old proceeding value
            // could probably just use a while loop but i don't feel like it
            i--;
        }

        // next, go through each string and check if they contain anything that's not a letter
        for (int k = 0; word1[i][k] != '\0'; k++) {
            if (!isalpha(word1[i][k])) {
                rotateLeftAll(word1, word2, separation, r, i);
                r--;
                i--;
            }
        }
        //literally the same thing but for the second string array
        for (int k = 0; word2[i][k] != '\0'; k++) {
            if (!isalpha(word2[i][k])) {
                rotateLeftAll(word1, word2, separation, r, i);
                r--;
                i--;
            }
        }

        // now remove any element positions where there are no characters ('')
        if (strcmp(word1[i], "") == 0 || strcmp(word2[i], "") == 0) {
            rotateLeftAll(word1, word2, separation, r, i);
            r--;
            i--;
        }

    }
    return r;
}

// here all you do is count how many times the words with 'separation' between them are found
// nowhere do you have to make sure the words are 'separation' apart
int rate(const char document[], const char word1[][MAX_WORD_LENGTH+1],
         const char word2[][MAX_WORD_LENGTH+1], const int separation[], int nPatterns) {

    return 0;
}
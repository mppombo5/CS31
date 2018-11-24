#include <iostream>
#include <cstring>
#include <cassert>
#include <cctype>
using namespace std;

const int MAX_WORD_LENGTH = 20;

const int MAX_DOC_LENGTH = 250;

void makeLowercase2D(char words[][MAX_WORD_LENGTH+1], int n);

void rotateLeftAll(char a1[][MAX_WORD_LENGTH+1], char a2[][MAX_WORD_LENGTH+1], int sep[], int n, int pos);

void rotateLeftOne(char a[], int n, int pos);

int makeProper(char word1[][MAX_WORD_LENGTH+1], char word2[][MAX_WORD_LENGTH+1],
               int separation[], int nPatterns);

int rate(const char document[], const char word1[][MAX_WORD_LENGTH+1],
         const char word2[][MAX_WORD_LENGTH+1], const int separation[], int nPatterns);

// nPatterns is the number of pairs of words in the arrays, could consider it the number in the first bracket
// therefore, nPatterns is the position of both words AND the separation value

int main() {

    const int TEST1_NRULES = 4;
    char test1w1[TEST1_NRULES][MAX_WORD_LENGTH+1] = {
            "mad",       "deranged", "nefarious", "have"
    };
    char test1w2[TEST1_NRULES][MAX_WORD_LENGTH+1] = {
            "scientist", "robot",    "plot",      "mad"
    };
    int test1dist[TEST1_NRULES] = {
            1,           3,          0,           12
    };
    assert(rate("The mad UCLA scientist unleashed a deranged evil giant robot.",
                test1w1, test1w2, test1dist, TEST1_NRULES) == 2);
    assert(rate("The mad UCLA scientist unleashed    a deranged robot.",
                test1w1, test1w2, test1dist, TEST1_NRULES) == 2);
    assert(rate("**** 2018 ****",
                test1w1, test1w2, test1dist, TEST1_NRULES) == 0);
    assert(rate("  That plot: NEFARIOUS!",
                test1w1, test1w2, test1dist, TEST1_NRULES) == 1);
    assert(rate("deranged deranged robot deranged robot robot",
                test1w1, test1w2, test1dist, TEST1_NRULES) == 1);
    assert(rate("That scientist said two mad scientists suffer from deranged-robot fever.",
                   test1w1, test1w2, test1dist, TEST1_NRULES) == 0);
    cout << "All tests succeeded" << endl;

    return 0;
}

void makeLowercase2D(char words[][MAX_WORD_LENGTH+1], int n) {

    for (int i = 0; i < n; i++) {
        for (int k = 0; words[i][k] != '\0'; k++) {
            words[i][k] = (char) tolower(words[i][k]);
        }
    }
}

void makeLowercase1D(char a[], int n) {

    for (int i = 0; i < n; i++) {
        a[i] = (char) tolower(a[i]);
    }
}

// use this function to remove the element at position pos and shift all other elements left
void rotateLeftAll(char a1[][MAX_WORD_LENGTH+1], char a2[][MAX_WORD_LENGTH+1], int sep[], int n, int pos) {

    for (int i = pos; i < (n-1); i++) {
        strcpy(a1[i], a1[i+1]);
        strcpy(a2[i], a2[i+1]);
        sep[i] = sep[i+1];
    }
}

void rotateLeftOne(char a[], int n, int pos) {

    for (int i = pos; i < (n-1); i++) {
        a[i] = a[i+1];
    }
}

int makeProper(char word1[][MAX_WORD_LENGTH+1], char word2[][MAX_WORD_LENGTH+1],
               int separation[], int nPatterns) {

    if (nPatterns <= 0)
        return 0;

    // make new number nPatternsNew which starts as nPatterns, decrease it as you remove patterns
    int nPatternsNew = nPatterns;

    makeLowercase2D(word1, nPatterns);
    makeLowercase2D(word2, nPatterns);

    bool removed;

    // check up to nPatternsNew, because the length of the array could change
    for (int i = 0; i < nPatternsNew; i++) {
        removed = false;
        // first, remove all elements in the arrays for which the separation value is negative
        if (separation[i] < 0) {
            rotateLeftAll(word1, word2, separation, nPatternsNew, i);

            nPatternsNew--;

            // decrease i so that it goes back over the same position, which now contains the old proceeding value
            // could probably just use a while loop but i don't feel like it
            i--;
            continue;
        }

        // next, go through each string and check if they contain anything that's not a letter
        for (int k = 0; word1[i][k] != '\0'; k++) {
            if (!isalpha(word1[i][k])) {
                rotateLeftAll(word1, word2, separation, nPatternsNew, i);
                nPatternsNew--;
                i--;
                removed = true;
                break;
            }
        }
        if (removed)
            continue;

        //literally the same thing but for the second string array
        for (int k = 0; word2[i][k] != '\0'; k++) {
            if (!isalpha(word2[i][k])) {
                rotateLeftAll(word1, word2, separation, nPatternsNew, i);
                nPatternsNew--;
                i--;
                removed = true;
                break;
            }
        }
        if (removed)
            continue;

        // remove any element positions where there are no characters ("")
        if (strcmp(word1[i], "") == 0 || strcmp(word2[i], "") == 0) {
            rotateLeftAll(word1, word2, separation, nPatternsNew, i);
            nPatternsNew--;
            i--;
            continue;
        }
    }

    // lastly, check for duplicates in either order
    // this one will probably be a bit more involved
    for (int i = 0; i < nPatternsNew; i++) {
        char tempWord1[MAX_WORD_LENGTH+1] = "";
        char tempWord2[MAX_WORD_LENGTH+1] = "";

        // create temporary string at word[i] for each iteration of the for loop
        strcpy(tempWord1, word1[i]);
        strcpy(tempWord2, word2[i]);

        for (int k = 0; k < nPatternsNew; k++) {
            // there are only 4 combinations of strings that would be equal; check for those
            if ( (k != i)
             && ((strcmp(tempWord1, word1[k]) == 0 && strcmp(tempWord2, word2[k]) == 0)
             ||  (strcmp(tempWord1, word2[k]) == 0 && strcmp(tempWord2, word1[k]) == 0))) {
                // remove the position for which separation is smaller
                if (separation[i] <= separation[k]) {
                    rotateLeftAll(word1, word2, separation, nPatternsNew, i);
                }
                else {
                    rotateLeftAll(word1, word2, separation, nPatternsNew, k);
                }
                nPatternsNew--;
                k--;
                continue;
            }
        }
    }
    return nPatternsNew;
}

int rate(const char document[], const char word1[][MAX_WORD_LENGTH+1],
         const char word2[][MAX_WORD_LENGTH+1], const int separation[], int nPatterns) {

    if (nPatterns <= 0)
        return 0;

    // create a copy of 'document' you can work with (make lowercase, make into proper form etc)
    char doc[MAX_DOC_LENGTH+1];
    // this might seem redundant, but when assert cases are run one
    // after the other it's not cleared, so there's garbage left over
    for (int i = 0; i < MAX_DOC_LENGTH+1; i++) {
        doc[i] = '\0';
    }
    strcpy(doc, document);

    makeLowercase1D(doc, MAX_DOC_LENGTH+1);

    // get rid of any characters that aren't letters or spaces
    for (int i = 0; doc[i] != '\0'; i++) {
        if (doc[i] != ' ' && !isalpha(doc[i])) {
            rotateLeftOne(doc, MAX_DOC_LENGTH+1, i);
            i--;
        }
    }

    // changes any instance of 2+ spaces into just 1 space
    for (int i = 1; doc[i] != '\0'; i++) {
        if (doc[i] == ' ' && doc[i-1] == ' ') {
            rotateLeftOne(doc, MAX_DOC_LENGTH+1, i);
            i--;
        }
    }
    if (doc[0] == ' ') {
        rotateLeftOne(doc, MAX_DOC_LENGTH+1, 0);
    }

    // put all the words from document[] into a new array, each as an element
    // make it more palatable than one long C string

    // create new 2D array to put created strings into
    // MAX_DOC_LENGTH should be a reasonable bound on word length
    char docAsArray[MAX_DOC_LENGTH+1][MAX_DOC_LENGTH+1];
    for (int i = 0; i < MAX_DOC_LENGTH+1; i++) {
        strcpy(docAsArray[i], "");
    }

    // main index to go through doc
    int index = 0;

    // changes to the start of each new string
    int charStart = 0;

    // counter for words in 2D array, to be used later
    int wordCounter = 0;

    // this is where all the words are put into docAsArray
    while (index < MAX_DOC_LENGTH+1 && doc[index] != '\0') {
        // temporary word to add to new string array
        char tempWord[MAX_DOC_LENGTH+1] = "";
        // make sure to check for the zero byte, otherwise it'll keep checking until it hits
        // who knows what space or where in memory
        while (doc[index] != ' ' && doc[index] != '\0') {
            index++;
        }
        int j = 0;
        for (int k = charStart; k < index; k++) {
            tempWord[j] = doc[k];
            j++;
        }
        // stick a zero byte on the end to finish the string
        tempWord[j+1] = '\0';
        // copy tempWord into the corresponding space in docAsArray
        strcpy(docAsArray[wordCounter], tempWord);
        index++;
        charStart = index;
        wordCounter++;
    }

    // docAsArray now has all the words in document, so now we can start counting the rates

    int rateCounter = 0;
    // outer loop for word1/word2
    for (int i = 0; i < nPatterns; i++) {
        bool foundMatch = false;
        // another loop to compare each word in docAsArray to word1[i]
        for (int k = 0; k < wordCounter; k++) {
            if (foundMatch)
                break;
            if (strcmp(docAsArray[k], word1[i]) == 0) {
                // startIndex to determine where to start the check for matching words – make 0 if
                // the current position in docAsArray minus separation of that value is less than 0
                int startIndex;
                // compare separation[i]+1 to k, as that'll give whether or not it's within bounds of docAsArray
                if ((k - (separation[i] + 1)) < 0)
                    startIndex = 0;
                else
                    startIndex = k - (separation[i] + 1);
                // increment until either j reaches i + separation[i], or until j reaches the end of docAsArray
                for (int j = startIndex; j < (k + (separation[i] + 1)) || j < wordCounter; j++) {
                    if (strcmp(docAsArray[j], word2[i]) == 0) {
                        rateCounter++;
                        foundMatch = true;
                        break;
                    }
                }
            }
        }
    }

    // debug statement to check that elements of docAsArray are correct
    /*for (int d = 0; d < wordCounter; d++) {
        cerr << docAsArray[d] << endl;
    }
    cerr << "This array contains " << wordCounter << " words.\n";*/

    return rateCounter;
}
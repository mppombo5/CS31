#include <iostream>
#include <cstring>
#include <cassert>
#include <cctype>
#include <cstdlib>
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

int testingMain() {

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

int d[3] =                      {    1,    0,    2 };
char w1[3][MAX_WORD_LENGTH+1] = { "aa", "bb", "cc" };
char w2[3][MAX_WORD_LENGTH+1] = { "dd", "ee", "ff" };

int e[2] =                      {    3,    3 };
char x1[2][MAX_WORD_LENGTH+1] = { "aa", "cc" };
char x2[2][MAX_WORD_LENGTH+1] = { "bb", "dd" };

const int THREE_LETTERS = 26*26*26;
int dd[THREE_LETTERS];
char ww1[THREE_LETTERS][MAX_WORD_LENGTH+1];
char ww2[THREE_LETTERS][MAX_WORD_LENGTH+1];

bool eq(int c, int dist, const char wd1[], const char wd2[])
{
    return d[c] == dist  &&  strcmp(w1[c], wd1) == 0  &&
           strcmp(w2[c], wd2) == 0;
}

void testone(int n)
{
    switch (n)
    {
        case  1: {
            assert(makeProper(w1, w2, d, 0) == 0);
        } break; case  2: {
            assert(makeProper(w1, w2, d, 1) == 1  &&
                   eq(0, 1, "aa", "dd"));
        } break; case  3: {
            d[0] = -1;
            assert(makeProper(w1, w2, d, 1) == 0);
        } break; case  4: {
            d[0] = -1;
            assert(makeProper(w1, w2, d, 2) == 1  &&
                   eq(0, 0, "bb", "ee"));
        } break; case  5: {
            d[1] = -1;
            assert(makeProper(w1, w2, d, 2) == 1  &&
                   eq(0, 1, "aa", "dd"));
        } break; case  6: {
            d[1] = -1;
            d[2] = -1;
            assert(makeProper(w1, w2, d, 3) == 1  &&
                   eq(0, 1, "aa", "dd"));
        } break; case  7: {
            d[0] = -1;
            d[1] = -1;
            assert(makeProper(w1, w2, d, 3) == 1  &&
                   eq(0, 2, "cc", "ff"));
        } break; case  8: {
            d[0] = -1;
            d[1] = -1;
            d[2] = -1;
            assert(makeProper(w1, w2, d, 3) == 0);
        } break; case  9: {
            strcpy(w1[1], "");
            assert(makeProper(w1, w2, d, 3) == 2  &&
                   ((eq(0, 1, "aa", "dd")  &&  eq(1, 2, "cc", "ff"))  ||
                    (eq(1, 1, "aa", "dd")  &&  eq(0, 2, "cc", "ff"))
                   )
            );
        } break; case 10: {
            strcpy(w2[1], "");
            assert(makeProper(w1, w2, d, 3) == 2  &&
                   ((eq(0, 1, "aa", "dd")  &&  eq(1, 2, "cc", "ff"))  ||
                    (eq(1, 1, "aa", "dd")  &&  eq(0, 2, "cc", "ff"))
                   )
            );
        } break; case 11: {
            strcpy(w1[1], "bb@");
            assert(makeProper(w1, w2, d, 3) == 2  &&
                   ((eq(0, 1, "aa", "dd")  &&  eq(1, 2, "cc", "ff"))  ||
                    (eq(1, 1, "aa", "dd")  &&  eq(0, 2, "cc", "ff"))
                   )
            );
        } break; case 12: {
            strcpy(w1[1], "bb ");
            assert(makeProper(w1, w2, d, 3) == 2  &&
                   ((eq(0, 1, "aa", "dd")  &&  eq(1, 2, "cc", "ff"))  ||
                    (eq(1, 1, "aa", "dd")  &&  eq(0, 2, "cc", "ff"))
                   )
            );
        } break; case 13: {
            strcpy(w1[1], "bBBb");
            assert(makeProper(w1, w2, d, 2) == 2  &&
                   ((eq(0, 1, "aa", "dd")  &&  eq(1, 0, "bbbb", "ee"))  ||
                    (eq(1, 1, "aa", "dd")  &&  eq(0, 0, "bbbb", "ee"))
                   )
            );
        } break; case 14: {
            strcpy(w1[1], "bBBb");
            strcpy(w2[1], "EeEeE");
            assert(makeProper(w1, w2, d, 2) == 2  &&
                   ((eq(0, 1, "aa", "dd")  &&  eq(1, 0, "bbbb", "eeeee"))  ||
                    (eq(1, 1, "aa", "dd")  &&  eq(0, 0, "bbbb", "eeeee"))
                   )
            );
        } break; case 15: {
            strcpy(w2[1], "bb");
            assert(makeProper(w1, w2, d, 2) == 2  &&
                   ((eq(0, 1, "aa", "dd")  &&  eq(1, 0, "bb", "bb"))  ||
                    (eq(1, 1, "aa", "dd")  &&  eq(0, 0, "bb", "bb"))
                   )
            );
        } break; case 16: {
            strcpy(w2[0], "aa");
            strcpy(w1[1], "aa");
            strcpy(w2[1], "aa");
            assert(makeProper(w1, w2, d, 2) == 1  &&
                   eq(0, 1, "aa", "aa")
            );
        } break; case 17: {
            strcpy(w1[1], "aa");
            strcpy(w2[1], "dd");
            assert(makeProper(w1, w2, d, 3) == 2  &&
                   ((eq(0, 1, "aa", "dd")  &&  eq(1, 2, "cc", "ff"))  ||
                    (eq(1, 1, "aa", "dd")  &&  eq(0, 2, "cc", "ff"))
                   )
            );
        } break; case 18: {
            strcpy(w1[1], "aa");
            strcpy(w2[1], "dd");
            d[1] = 1;
            assert(makeProper(w1, w2, d, 3) == 2  &&
                   ((eq(0, 1, "aa", "dd")  &&  eq(1, 2, "cc", "ff"))  ||
                    (eq(1, 1, "aa", "dd")  &&  eq(0, 2, "cc", "ff"))
                   )
            );
        } break; case 19: {
            strcpy(w1[1], "aa");
            strcpy(w2[1], "dd");
            d[1] = 4;
            assert(makeProper(w1, w2, d, 3) == 2  &&
                   ((eq(0, 4, "aa", "dd")  &&  eq(1, 2, "cc", "ff"))  ||
                    (eq(1, 4, "aa", "dd")  &&  eq(0, 2, "cc", "ff"))
                   )
            );
        } break; case 20: {
            strcpy(w1[1], "aa");
            strcpy(w2[1], "dd");
            strcpy(w1[2], "aa");
            strcpy(w2[2], "dd");
            assert(makeProper(w1, w2, d, 3) == 1  &&
                   eq(0, 2, "aa", "dd")
            );
        } break; case 21: {
            strcpy(w1[2], "aa");
            strcpy(w2[2], "dd");
            d[1] = -1;
            assert(makeProper(w1, w2, d, 3) == 1  &&
                   eq(0, 2, "aa", "dd")
            );
        } break; case 22: {
            strcpy(w1[1], "abcdefghijklmnopqrst");
            strcpy(w2[1], "abcdefghijklmnopqrsu");
            d[0] = -1;
            assert(makeProper(w1, w2, d, 2) == 1  &&
                   eq(0, 0, "abcdefghijklmnopqrst",
                      "abcdefghijklmnopqrsu")
            );
        } break; case 23: {
            strcpy(w2[0], "DD");
            strcpy(w1[1], "AA");
            strcpy(w2[1], "dD");
            assert(makeProper(w1, w2, d, 3) == 2  &&
                   ((eq(0, 1, "aa", "dd")  &&  eq(1, 2, "cc", "ff"))  ||
                    (eq(1, 1, "aa", "dd")  &&  eq(0, 2, "cc", "ff"))
                   )
            );
        } break; case 24: {
            strcpy(w1[1], "dd");
            strcpy(w2[1], "aa");
            assert(makeProper(w1, w2, d, 3) == 2  &&
                   ((eq(0, 1, "aa", "dd")  &&  eq(1, 2, "cc", "ff"))  ||
                    (eq(1, 1, "aa", "dd")  &&  eq(0, 2, "cc", "ff"))
                   )
            );
        } break; case 25: {
            strcpy(w1[1], "dd");
            strcpy(w2[1], "aa");
            d[1] = 1;
            assert(makeProper(w1, w2, d, 3) == 2  &&
                   (((eq(0, 1, "aa", "dd")  ||  eq(0, 1, "dd", "aa")
                     )  &&  eq(1, 2, "cc", "ff")
                    )  ||
                    ((eq(1, 1, "aa", "dd")  ||  eq(1, 1, "dd", "aa")
                     )  &&  eq(0, 2, "cc", "ff")
                    )
                   )
            );
        } break; case 26: {
            strcpy(w1[1], "Dd");
            strcpy(w2[1], "aA");
            assert(makeProper(w1, w2, d, 3) == 2  &&
                   ((eq(0, 1, "aa", "dd")  &&  eq(1, 2, "cc", "ff"))  ||
                    (eq(1, 1, "aa", "dd")  &&  eq(0, 2, "cc", "ff"))
                   )
            );
        } break; case 27: {
            int dx[7] = { 1, 3, 0, 2, 1, 0, 12 };
            char w1x[7][MAX_WORD_LENGTH+1] = { "mad", "deranged",
                                               "NEFARIOUS", "half-witted", "robot", "plot", "have" };
            char w2x[7][MAX_WORD_LENGTH+1] = { "scientist", "robot",
                                               "PLOT", "assistant", "deranged", "Nefarious", "mad" };
            assert(makeProper(w1x, w2x, dx, 7) == 4);
        } break; case 28: {
            assert(rate("", x1, x2, e, 2) == 0);
        } break; case 29: {
            assert(rate(" ", x1, x2, e, 2) == 0);
        } break; case 30: {
            assert(rate("aa bb", x1, x2, e, 2) == 1);
        } break; case 31: {
            e[0] = 0;
            assert(rate("aa bb", x1, x2, e, 2) == 1);
        } break; case 32: {
            e[0] = 0;
            assert(rate("aa     bb", x1, x2, e, 2) == 1);
        } break; case 33: {
            assert(rate(" aa bb", x1, x2, e, 2) == 1);
        } break; case 34: {
            assert(rate("aa bb ", x1, x2, e, 2) == 1);
        } break; case 35: {
            assert(rate("aa bb cc dd xx", x1, x2, e, 2) == 2);
        } break; case 36: {
            assert(rate("aa bb cc dd xx", x1, x2, e, 1) == 1);
        } break; case 37: {
            assert(rate("aa xx cc bb xx dd xx", x1, x2, e, 2) == 2);
        } break; case 38: {
            assert(rate("xx dd bb cc aa xx", x1, x2, e, 2) == 2);
        } break; case 39: {
            assert(rate("aa xx xx xx bb cc dd xx", x1, x2, e, 2) == 2);
        } break; case 40: {
            assert(rate("aa xx xx xx xx bb cc dd xx", x1, x2, e, 2) == 1);
        } break; case 41: {
            e[0] = 0;
            e[1] = 0;
            assert(rate("aa xx bb cc dd xx", x1, x2, e, 2) == 1);
        } break; case 42: {
            e[0] = 1;
            e[1] = 1;
            assert(rate("aa cc bb dd xx", x1, x2, e, 2) == 2);
        } break; case 43: {
            assert(rate("aa bb aa bb cc dd xx", x1, x2, e, 2) == 2);
        } break; case 44: {
            assert(rate("aa aa bb bb cc dd xx", x1, x2, e, 2) == 2);
        } break; case 45: {
            strcpy(x2[0], "aa");
            assert(rate("aa xx xx aa", x1, x2, e, 2) == 1);
        } break; case 46: {
            strcpy(x2[0], "aa");
            assert(rate("xx aa xx", x1, x2, e, 2) == 0);
        } break; case 47: {
            assert(rate("aA bb cc dd xx", x1, x2, e, 2) == 2);
        } break; case 48: {
            assert(rate("aa @@ ## $$ %% ^^ bb cc dd xx", x1, x2, e, 2) == 2);
        } break; case 49: {
            assert(rate("aa b@@b cc dd xx", x1, x2, e, 2) == 2);
        } break; case 50: {
            assert(rate("aa b123456789012345678901234567890b cc dd xx", x1, x2, e, 2) == 2);
        } break; case 51: {
            e[0] = 0;
            assert(rate("aa abcdefghijklmnopqrstuvwxyz bb cc dd xx", x1, x2, e, 2) == 1);
        } break; case 52: {
            e[0] = 1;
            assert(rate("aa abcdefghijklmnopqrstuvwxyz bb cc dd xx", x1, x2, e, 2) == 2);
        } break; case 53: {
            strcpy(x1[0], "abcdefghijklmnopqrst");
            assert(rate("abcdefghijklmnopqrst bb cc dd xx", x1, x2, e, 2) == 2);
        } break; case 54: {
            strcpy(x1[0], "abcdefghijklmnopqrst");
            assert(rate("abcdefghijklmnopqrstu bb cc dd xx", x1, x2, e, 2) == 1);
        } break; case 55: {
            assert(rate("aaa bb cc dd xx", x1, x2, e, 2) == 1);
        } break; case 56: {
            assert(rate("aa@bb cc dd xx", x1, x2, e, 2) == 1);
        } break; case 57: {
            assert(rate("aa bb@cc dd xx", x1, x2, e, 2) == 0);
        } break; case 58: {
            e[0] = 1000;
            assert(rate("xx aa xx", x1, x2, e, 2) == 0);
        } break; case 59: {
            strcpy(x1[0], "a");
            strcpy(x2[0], "b");
            e[0] = 123;
            char doc[250+1];
            strcpy(doc, "a ");
            for (int k = 0; k < 123; k++)
                strcpy(doc+2+2*k, "x ");
            strcpy(doc+248, "b ");
            assert(rate(doc, x1, x2, e, 2) == 1);
        } break; case 60: {
            for (int k = 0; k < THREE_LETTERS; k++)
            {
                dd[k] = (k % 2) - 1;
                strcpy(ww1[k], "a");
                strcpy(ww2[k], "aaa");
                int kk = k;
                ww2[k][2] += kk % 26;
                kk /= 26;
                ww2[k][1] += kk % 26;
                kk /= 26;
                ww2[k][0] += kk;
            }
            assert(makeProper(ww1, ww2, dd, THREE_LETTERS) == THREE_LETTERS / 2);
            for (int k = 0; k < THREE_LETTERS / 2; k++)
                assert(dd[k] == 0 && strcmp(ww1[k], "a") == 0 &&
                       islower(ww2[k][2]) &&
                       (ww2[k][2] - 'a') % 2 == 1);
        } break; case 61: {
            for (int k = 0; k < THREE_LETTERS; k++)
            {
                dd[k] = 0;
                strcpy(ww1[k], "a");
                strcpy(ww2[k], "aaa");
                int kk = k;
                ww2[k][2] += kk % 26;
                kk /= 26;
                ww2[k][1] += kk % 26;
                kk /= 26;
                ww2[k][0] += kk;
            }
            assert(rate("a aaa a iaa a pzz a zzz", ww1, ww2, dd, THREE_LETTERS) == 4);
            assert(rate("a aaaa a iaaa a pzzz a zzzz", ww1, ww2, dd, THREE_LETTERS) == 0);
        } break;
    }
}

int main()
{
    cout << "Enter a test number (1 to 61): ";
    int n;
    cin >> n;
    if (n < 1  ||  n > 61)
    {
        cout << "Bad test number" << endl;
        return 1;
    }
    testone(n);
    cout << "Passed test " << n << endl;
}
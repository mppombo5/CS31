#include <iostream>
#include <string>
#include <cctype>
using namespace std;

void makeUpperCase(string& text);
bool hasProperSyntax(string pollData);
int tallySeats(string pollData, char party, int& seatTally);
bool isValidUppercaseStateCode(string stateCode);

int main() {

    string pollString;
    char party;
    int seats;

    for (;;) {
        cout << "What is your poll data string? ";
        getline(cin, pollString);

        if (pollString == "exit")
            break;

        cout << "What party would you like to tally? (one letter): ";
        cin >> party;

        tallySeats(pollString, party, seats);

        int tallyReturn = tallySeats(pollString, party, seats);

        switch (tallyReturn) {
            case 0:
                cout << "Party " << party << " is forecasted to win " << seats << " seats.\n";
                break;
            case 1:
                cout << "You entered an invalid poll string.\n";
                break;
            case 2:
                cout << "You entered a party value that is not a letter.\n";
                break;
            default:
                cout << "What on earth did you do? I can't help you here, bud.\n";
                break;
        }

        cout << "tallySeats returned value " << tallyReturn << ".\n";
        cin.ignore(10000, '\n');
    }

    return 0;
}

// it's easier to deal with checking for characters if you only have to check for uppercase ones.
void makeUpperCase(string& text) {
    for (int i = 0; i != text.size(); i++) {
        text[i] = (char) toupper(text[i]);
    }
}

bool hasProperSyntax(string pollData) {
    // this makes it easier to check for char's
    makeUpperCase(pollData);

    // must accept empty strings, but 1-char long strings will never work
    switch (pollData.size()) {
        case 0:
            return true;
        case 1:
            return false;
        default:
            break;
    }

    size_t k = 0;
    // better than != pollData.size() because of the way we increment
    while (k < pollData.size()) {

        // if the first two characters are not letters, return false.
        if (!(isalpha(pollData[k]) && isalpha(pollData[k+1]))) {
            return false;
        }
        else {
            if (!isValidUppercaseStateCode(pollData.substr(k, 2))) {
                return false;
            }
            k += 2;
        }

        // go through the rest of the string until you hit a comma
        while (pollData[k] != ',') {
            // if the string is at its end, break out of the while loop
            if (k == pollData.size()){
                break;
            }

            if (isdigit(pollData[k])) {
                k++;

                // case for a letter following 2 numbers
                if (isdigit(pollData[k])) {
                    k++;
                    if (isalpha(pollData[k])) {
                        k++;
                    }
                    else {
                        return false;
                    }
                }
                // case for a letter following one number
                else if (isalpha(pollData[k])) {
                    k++;
                }
                else {
                    return false;
                }
            }
            else {
                return false;
            }
        }


        // if the end of one state's string is reached and the next character is a comma,
        // go back through the while loop and check for the next state's string
        if (pollData[k] == ',') {
            k++;
            continue;
        }
        // return false if there is more to the string after everything is checked,
        // and it's not separated by a comma.
        else {
            if (k < pollData.size()) {
                return false;
            }
        }
    }

    // make sure a the PDS doesn't end in a comma
    return (pollData[pollData.size() - 1] != ',');
}

int tallySeats(string pollData, char party, int& seatTally) {

    // here it is necessary, so you only have to check for uppercase cases
    makeUpperCase(pollData);

    // return 1 if the string is not a valid poll data string
    if (!hasProperSyntax(pollData)) {
        return 1;
    }

    // return 2 if the party character is not a letter
    else if (!isalpha(party)) {
        return 2;
    }

    // this might be redundant, but it's better to be safe than sorry.
    // I chose 1 for the case of both occurring.
    else if (!hasProperSyntax(pollData) && !isalpha(party)) {
        return 1;
    }

    seatTally = 0;

    size_t k = 0;
    while (k < pollData.size()) {
        // advance through the string until you hit a number
        while (!isdigit(pollData[k])) {
            k++;
            if (k >= (pollData.size() - 1))
                break;
        }
        if (k >= (pollData.size() - 1))
            break;
        // check if the character one ahead of the digit is a letter
        if (isalpha(pollData[k+1])) {
            if (pollData[k+1] == toupper(party)) {
                // this is to make the character at position k a number
                int added = pollData[k] - '0';
                seatTally += added;
            }
            k+=2;
        }
        // check if the character 2 spots ahead of the number is a letter
        else if (isalpha(pollData[k+2])) {
            if (pollData[k+2] == toupper(party)) {
                // this turns both digit characters into integers,
                // multiplies the first number by 10, and adds them
                int addedOnes = pollData[k+1] - '0';
                int addedTens = (pollData[k] - '0') * 10;
                int totalAdded = addedOnes + addedTens;
                seatTally += totalAdded;
            }
            k+=3;
        }
        else {
            k++;
        }
    }

    return 0;
}

// Return true if the argument is a two-uppercase-letter state code, or
// false otherwise.
bool isValidUppercaseStateCode(string stateCode) {
    const string codes =
            "AL.AK.AZ.AR.CA.CO.CT.DE.FL.GA.HI.ID.IL.IN.IA.KS.KY."
            "LA.ME.MD.MA.MI.MN.MS.MO.MT.NE.NV.NH.NJ.NM.NY.NC.ND."
            "OH.OK.OR.PA.RI.SC.SD.TN.TX.UT.VT.VA.WA.WV.WI.WY";
    return (stateCode.size() == 2 &&
            stateCode.find('.') == string::npos  &&  // no '.' in stateCode
            codes.find(stateCode) != string::npos);  // match found
}
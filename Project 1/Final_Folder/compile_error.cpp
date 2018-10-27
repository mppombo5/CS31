// Code for Project 1
// Report poll results

#include <iostream>

int main()
{
    int numberSurveyed
    int forNewsom
    int forCox
    
    cout << "How many registered voters were surveyed? "
    cin >> numberSurveyed
    cout << "How many of them say they will vote for Newsom?
    cin >> forNewsom
    cout << "How many of them say they will vote for Cox? "
    cin >> forCox
    
    double pctNewsom = 100.0 * forNewsom / numberSurveyed
    double pctCox = 100.0 * forCox / numberSurveyed
    
    cout.setf(ios::fixed)       // see pp. 32-33 in Savitch 6/e
    cout.precision(1)
    
    cout << endl
    cout << pctNewsom << "% say they will vote for Newsom." << endl
    cout << pctCox << "% say they will vote for Cox." << endl
    
    if (forNewsom > forCox)
        cout << "Newsom is predicted to win the election." << endl
    else
        cout << "Cox is predicted to win the election." << endl
}

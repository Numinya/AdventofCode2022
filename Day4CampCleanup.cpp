#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

struct assignment
{
    int lower;
    int upper;
};

// converts a vector of digits into a single number
int convertDigitNum(const vector<int> &d)
{
    int num = 0, tenpower, digit ;
    for (int i = 0; i < d.size(); i++)
    {
        num += (d[i] % 48) * pow(10, d.size() - i-1);
    }

    return num;
}


// takes the input of "aa-bb,cc-dd" into ints
void distributeInput(assignment &a1, assignment &a2, const string &str)
{
    vector<int> digits;                                        // holds the digits of every number
    vector<int> inpnumbers;                                    // holds the numbers themselves

    // loop through each char in the string
    for (int i = 0; i < str.length(); i++)
    {
        if (str[i] == 45 or str[i] == 44)                       // if the letter is '-' or ','
        {
            inpnumbers.push_back(convertDigitNum(digits));      // convert to number and reset
            digits.clear();
        }      

        else
        {
            digits.push_back(str[i] % 48);                      // otherwise add a digit to digits
        }
    }

    inpnumbers.push_back(convertDigitNum(digits));

    // distribute numbers
    a1.lower = inpnumbers[0];
    a1.upper = inpnumbers[1];

    a2.lower = inpnumbers[2];
    a2.upper = inpnumbers[3];
}


// outputs whether all of one assignment is contained in the other
// used in part 1)
bool contains(const assignment &a1, const assignment &a2)
{
    return (a1.lower >= a2.lower && a1.upper <= a2.upper);
}



// outputs whether any of assignment 1 overlaps with assignment 2
// used in part 2)
bool overlaps(const assignment &a1, const assignment &a2)
{
    return (a1.upper >= a2.lower && a2.upper >= a1.lower);
}

void part1()
{
    string input;
    assignment first;
    assignment second;

    int sum = 0;

    while (getline(cin, input))
    {
        distributeInput(first, second, input);

        if (contains(first, second) || contains(second, first))
        {sum++;}
    }

    cout << endl << sum;
}



void part2()
{
    string input;
    assignment first;
    assignment second;

    int sum = 0;

    while (getline(cin, input))
    {
        distributeInput(first, second, input);

        if (overlaps(first, second))
        {sum++;}

    }

    cout << endl << sum;
}

int main()
{
    part1();
    part2();

    
    return 0;
}
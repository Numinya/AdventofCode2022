#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;



int main()
{
    // variable setup
    int max = 0, sum = 0;
    vector<int> calories;

    string n; 

    // take inputs
    while (getline(cin, n))
    {
        if (n == "")                                          // when line is empty
        {
            if (sum > max)
            {max = sum;}

            calories.push_back(sum);

            sum = 0;                                           
        }


        else if (n == "bruh")                                  // exit flag bc idk how else
        {break;}

        else 
        {sum += stoi(n);}                                      // convert string to int and add

    }

    cout << endl << max << endl;                               // part a) output

    sort(calories.begin(), calories.end(), greater <>());  
    cout << calories[0] + calories[1] + calories[2];           // part b) output


    return 0;
}
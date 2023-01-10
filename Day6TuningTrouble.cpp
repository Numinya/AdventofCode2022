#include <iostream>
#include <vector>

using namespace std;

bool exists_in (const vector<char> &v, char c)
{
    bool found = false;
    for (int i = 0; i < v.size(); i++)
    {
        if (v[i] == c)
        {
            found = true;
        }
    }

    return found;
}

void part1()
{
    string signal;
    cin >> signal;

    vector<char> setoffour;

    for (int i = 3; i < signal.length() + 1; i++)
    {
        setoffour.clear();

        for (int j = 0; j < 4; j++)
        {
            if (!exists_in(setoffour, signal[i-j]))
            {
                setoffour.push_back(signal[i-j]);
            }
        }

        if (setoffour.size() == 4)
        {
            cout << endl << ++i;
            break;
        }
    }

}

void part2()
{
    string signal;
    cin >> signal;
    
    
    vector<char> setof14;

    for (int i = 13; i < signal.length() + 1; i++)
    {
        setof14.clear();

        for (int j = 0; j < 14; j++)
        {
            if (!exists_in(setof14, signal[i-j]))
            {
                setof14.push_back(signal[i-j]);
            }
        }

        if (setof14.size() == 14)
        {
            cout << endl << ++i;
            break;
        }
    }

}

int main()
{
    part1();

    part2();

    return 0;
}
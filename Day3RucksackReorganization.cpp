#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// converts a char into the correct int
// a-z -> 0-26 and A-Z -> 27-56
int convertpriority(char item)
{
    if (65 <= item && item <= 90)
    {return (item % 64 + 26);}

    else 
    {return (item % 96);}
}

// creates a vector of chars given a string where each element is a letter 
void createCompartment(vector<char> &component, string inventory, int start, int end)
{
    component.clear();

    for (int i = start; i < end; i++)
    {component.push_back(inventory[i]);}
}

// checks if item exists in component
bool exists(vector<char> component, char item)
{
    int i = 0;
    while(i < component.size() && i < item)
    {
        if (component[i] == item)
        {return true;}

        i++;
    }

    return false;
}

void part1()
{
    // variable setup
    int priority, size, sum = 0;

    string inventory;
    vector<char> first;
    vector<char> second;

    // start
    while (cin >> inventory)
    {
        // setting up vectors
        size = inventory.length();

        createCompartment(first, inventory, 0, size/2);
        createCompartment(second, inventory, size/2, size);

        sort(first.begin(), first.end());
        sort(second.begin(), second.end());

        // delete any repeat items
        first.erase(unique(first.begin(), first.end()), first.end());
        second.erase(unique(second.begin(), second.end()), second.end());

        // while either component is empty
        while(!first.empty() && !second.empty())
        {
            // when both letters exist in both compartments
            if(first.back() == second.back())
            {
                priority = (convertpriority(first.back())); // convert char into custom int
                sum += priority;
                first.pop_back();
                second.pop_back();
            }

            
            else if (first.back() > second.back())          // remove letter when not common
            {first.pop_back();}

            
            else
            {second.pop_back();}                            // remove letter when not common
        }     
    }

    cout << endl << sum;

}

void part2()
{
    // variable setup
    int size, sum = 0;

    string inv1, inv2, inv3;
    vector<char> first;
    vector<char> second;
    vector<char> third;

    // start 
    while(cin >> inv1 && cin >> inv2 && cin >> inv3)
    {
        // setting up vectors
        createCompartment(first, inv1, 0, inv1.length());
        createCompartment(second, inv2, 0, inv2.length());
        createCompartment(third, inv3, 0, inv3.length());

        sort (first.begin(), first.end());
        sort(second.begin(), second.end());
        sort(third.begin(), third.end());

        first.erase(unique(first.begin(), first.end()), first.end());
        second.erase(unique(second.begin(), second.end()), second.end());
        third.erase(unique(third.begin(), third.end()), third.end());


        // setup
        while(!first.empty() && !second.empty())
        {
            // if a letter exists in both first and second
            if(first.back() == second.back())
            {
                // check if letter exists in third
                if(exists(third, first.back()))
                {
                    sum += convertpriority(first.back());
                    break;              
                }

                // otherwise remove 
                else 
                {
                    first.pop_back();
                    second.pop_back();
                }
                
            }

            // remove letter when not common
            else if (first.back() > second.back())
            {first.pop_back();}

            // remove letter when not common
            else
            {second.pop_back();}
        }     
    
    }
    cout << endl << sum;

}

int main()
{ 
    part1();

    part2();

    return 0;
}
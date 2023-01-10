#include <iostream>
#include <queue>
#include <vector>
#include <cmath>

using namespace std;

struct monkey
{
    queue<long long> items;
    char operation;
    int operationnum;
    int testnum;
    int truemonkey;
    int falsemonkey;

    int inspectnum = 0;

    void inspect()
    {
        if (operation == '+')
        {
            items.front() += operationnum;
        }

        else if (operation == '*')
        {
            items.front() *= operationnum;
        }

        else 
        {
            items.front() = pow(items.front(), 2);
        }

        inspectnum++;
    }

    void bored()
    {
        items.front() /= 3;
    }

    void throwsto(vector<monkey> &v)
    {
        if (items.front() % testnum == 0)
        {
            v[truemonkey].items.push(items.front());
        }
        
        else
        {
            v[falsemonkey].items.push(items.front());
        }

        items.pop();
    }

    void inspect2(int m)
    {
        if (operation == '+')
        {
            items.front() += operationnum;
        }

        else if (operation == '*')
        {
            items.front() *= operationnum;
        }

        else 
        {
            items.front() = pow(items.front(), 2);
        }

        items.front() %= m;
        inspectnum++;
    }
};

int chartoint(char c)
{
    return c - '0';
}

string takeint(const string &str, int start)
{
    string temp;
    for (int i = start; i < str.size(); i++)
    {
        temp.push_back(str[i]);
    }

    return temp;
}

void getInput(vector<monkey> &m)
{
    string input, tempint;
    monkey temp;
    bool done = false;

    while(getline(cin, input))
    {
        
        //parse items
        getline(cin, input);
        input.push_back(',');
        for (int i = 18; i < input.size(); i++)
        {
            if (input[i] == ',')
            {
                temp.items.push(stoll(tempint));
                tempint.clear();
            }

            else if (input[i] != ' ')
            {
                tempint.push_back(input[i]);
            }
            
        }
       

        // parse operation
        getline(cin, input);
        temp.operation = input[23];
        tempint = takeint(input, 25);
        if (tempint == "old")
        {
            temp.operationnum = 2;
            temp.operation = '^';
        }

        else 
        {
            temp.operationnum = stoll(tempint);
        }
        tempint.clear();

        

        // parse tests
        getline(cin, input);
        temp.testnum = stoll(takeint(input, 21));

        getline(cin,input);
        temp.truemonkey = chartoint(input[29]);

        getline(cin,input);
        temp.falsemonkey = chartoint(input[30]);

        //blank line
        getline(cin, input);

        // add vectors
        m.push_back(temp);
        queue<long long>().swap(temp.items); 
    }
}

void monkeyround(vector<monkey> &monkeys)
{
    for (int i = 0; i < monkeys.size(); i++)
    {
        while(!monkeys[i].items.empty())
        {
            monkeys[i].inspect();
            monkeys[i].bored();
            monkeys[i].throwsto(monkeys);
        }
    }
}

long long output(vector<monkey> &monkeys)
{
    long long max1 = monkeys[0].inspectnum;
    long long max2 = monkeys[1].inspectnum;
    for (int i = 2; i < monkeys.size(); i++)
    {
        if (monkeys[i].inspectnum > max1)
        {
            max2 = max1;
            max1 = monkeys[i].inspectnum;
        }

        else if (monkeys[i].inspectnum > max2)
        {
            max2 = monkeys[i].inspectnum;
        }
    }

    long long ans = max1 * max2;
    return ans;
}

void part1()
{
    vector<monkey> monkeys;
    getInput(monkeys);

    // loop through 20 rounds
    for (int i = 0; i < 20; i++)
    {
        monkeyround(monkeys);
    }

    cout << output(monkeys);  
}

int findmodulus(vector<monkey> &monkeys)
{
    int m = 1;
    for (int i = 0; i < monkeys.size(); i++)
    {
        m *= monkeys[i].testnum;
    }

    return m;
}

void monkeyround2(vector<monkey> &monkeys, int m)
{
    for (int i = 0; i < monkeys.size(); i++)
    {
        while(!monkeys[i].items.empty())
        {
            monkeys[i].inspect2(m);
            monkeys[i].throwsto(monkeys);
        }
    }
}

void part2()
{
    vector<monkey> monkeys;
    getInput(monkeys);
    int m = findmodulus(monkeys);

    // loop through 10000 rounds
    for (int i = 0; i < 10000; i++)
    {
       monkeyround2(monkeys, m);
       
    }

    cout << output(monkeys); 
}

int main()
{
    // part1 has been modified to fit part 2
    part1();

    part2();

    return 0;
}
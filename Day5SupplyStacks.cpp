#include <iostream>
#include <stack>
#include <vector>
#include <string>

using namespace std;



void getInput(stack<char> &c, int &num)
{
    string input;

    while(getline(cin, input) && input[1] != '1')
    {
        // select only the indices that have a letter
        // and push it onto the stack
        for(int i = 1; i < input.length() - 1; i+= 4)
        {
            // '[]' are not letters so we ignore
            if(input[i] != '[' && input[i] != ']')
            {
                c.push(input[i]);
            }
        }
    }

    // simple calculations to how many stacks there are
    num = (input.length()- 2) / 4 + 1;


}

void createstacks(stack<char> &allcargo, vector<stack<char>> &cargostacks, int size)
{
    while(!(allcargo.empty()))
    {
        // loop through one set of stacks
        for(int i = size-1; i >= 0; i--)
        {
            // if top is not empty push it onto corresponding stack
            if(allcargo.top() != ' ')
            {
                cargostacks[i].push(allcargo.top());
            }

            allcargo.pop();
        } 
    }
    
}

void removeemptyline()
{
    string del;

    getline(cin, del); 
}

void getnumbers(int &num, int &s, int &d, string str)
{
    bool firstspace = true;
    string tempnum;
    vector<int> distribute;

    str += ' ';
    for(int i = 5; i < str.length(); i++)
    {
        if (str[i] == ' ')
        {
            if (firstspace)
            {
                firstspace = !firstspace;      // firstspace becomes false
                distribute.push_back(stoi(tempnum));
                tempnum = "";
            }

            else                               // else is the current index is not the firstspace
            {
                firstspace = !firstspace;
                
            }
        }

        else if (firstspace)
        {
            tempnum += str[i];
        }
    }

    num = distribute[0];
    s = --distribute[1];
    d = --distribute[2];
}

void output(const vector<stack<char>> &c)
{
    string message;
    for(int i = 0; i < c.size(); i++)
    {
        if (!c[i].empty())
        {
            message += c[i].top();
        }
    }

    cout << endl << message;
}

void part1()
{
    // processing input input
    int stacknum;
    stack<char> allcargo;
    getInput(allcargo, stacknum);

    // create structure for the stacks of letters
    vector<stack<char>> cargostacks(stacknum);
    createstacks(allcargo, cargostacks, stacknum);

    removeemptyline();


    // start of program
    string move;
    // index of stack, original stack, final stack
    int boxnum, start, destination;

    while(getline(cin, move))
    {
        getnumbers(boxnum, start, destination, move);

        for (int i = 0; i < boxnum; i++)
        {
            // add the first start block into the placeholder stack
            cargostacks[destination].push(cargostacks[start].top());

            // remove the block from the start
            cargostacks[start].pop();
        }
    }
    
    output(cargostacks);
    
}

void part2()
{
    // processing input input
    int stacknum;
    stack<char> allcargo;
    getInput(allcargo, stacknum);

    // create structure for the stacks of letters
    vector<stack<char>> cargostacks(stacknum);
    createstacks(allcargo, cargostacks, stacknum);

    removeemptyline();


    string move;
    int boxnum, start, destination;
    stack<char> placeholder;

    while(getline(cin, move))
    {
        getnumbers(boxnum, start, destination, move);

        for(int i = 0; i < boxnum; i++)
        {
            placeholder.push(cargostacks[start].top());
            cargostacks[start].pop();
        }

        for (int i = 0; i < boxnum; i++)
        {
            cargostacks[destination].push(placeholder.top());
            placeholder.pop();
        }
    }

    output(cargostacks);
}

int main()
{
    //part1();

    part2();


    return 0;
}
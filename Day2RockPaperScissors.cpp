#include <iostream>
#include <vector>

using namespace std;


// points for result
int loss = 0;
int draw = 3;
int win = 6;

// points for choice
int rock = 1;
int paper = 2;
int scissors = 3;

int problemA()
{
    char opponent, suggest;
    int totalscore = 0; 
    while (cin >> opponent, cin >> suggest)
    {
        // rock
        if (opponent == 'A')    
        {
            if (suggest == 'X')
            {totalscore += rock + draw;}

            else if (suggest == 'Y')
            {totalscore += paper + win;}

            else
            {totalscore += scissors + loss;}
        }

        // paper
        else if (opponent == 'B')
        {
            if (suggest == 'X')
            {totalscore += rock + loss;}

            else if (suggest == 'Y')
            {totalscore += paper + draw;}

            else 
            {totalscore += scissors + win;}
        }

        // scissors
        else 
        {
            if (suggest == 'X')
            {totalscore += rock + win;}

            else if (suggest == 'Y')
            {totalscore += paper + loss;}

            else 
            {totalscore += scissors + draw;}
        } 

    }
    
    return totalscore;
}

int problemB()
{
    char opponent, suggest;
    int totalscore = 0;
    while (cin >> opponent && cin >> suggest)
    {
        if (opponent == 'A')      
        {
            if (suggest == 'X')
            {totalscore += scissors + loss;}

            else if (suggest == 'Y')
            {totalscore += rock + draw;}

            else
            {totalscore += paper + win;}
        }

        // paper
        else if (opponent == 'B')
        {
            if (suggest == 'X')
            {totalscore += rock + loss;}

            else if (suggest == 'Y')
            {totalscore += paper + draw;}

            else 
            {totalscore += scissors + win;}
        }

        // scissors
        else 
        {
            if (suggest == 'X')
            {totalscore += paper + loss;}

            else if (suggest == 'Y')
            {totalscore += scissors + draw;}

            else 
            {totalscore += rock + win;}
            }
    } 

    return totalscore;
}


int main()
{
    // variable setup
    int totalscore = 0;

    // input variables
    char opponent, suggest;
    string problem;
    cin >> problem;


    // start
    if (problem == "a")
    {cout << problemA();}

    else
    {cout << problemB();}

    return 0;
}
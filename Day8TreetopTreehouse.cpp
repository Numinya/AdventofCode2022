#include <iostream>
#include <vector>
#include <string>

using namespace std;

// converts a digit in char form to int
int ctoi (char c)
{
    return (c % 48);
}

// creates a matrix of trees
void getinput(vector<vector<int>> &v)
{
    string row;
    vector<int> temp;
    while(getline(cin,row))
    {
        for (int i = 0; i < row.length(); i++)
        {
            // add digit to a temporary vector
            temp.push_back(ctoi(row[i]));
        }

        // add the entire row to the forest
        v.push_back(temp);
        // reset the temporary vector
        temp.clear();
    }
}

int checkupdown(vector<vector<int>> forest, int tree, int start, int end, int col)
{
    bool shorter = false;

    for (int i = start; i < end; i++)
    {
        if (forest[i][col] >= tree)
        {
            
            shorter = true;
            break;
        }
    }

    return shorter;
}


// new idea we put an if statement beforehand
int checktree(const vector<vector<int>> &forest, int tree, int row, int col)
{
    // check up
    for (int i = 0; i < row; i++)
    {
        if (forest[i][col] >= tree)
        {
            break;
        }

        else if (i == row - 1)
        {
            return 1;
        }
    }

    // check down
    for (int i = row + 1; i < forest.size(); i++)
    {
        if (forest[i][col] >= tree)
        {
            break;
        }

        else if (i == forest.size() - 1)
        {
            return 1;
        }
    }

    for (int i = 0; i < col; i++)
    {
        if (forest[row][i] >= tree)
        {
            break;
        }

        else if  (i == col - 1)
        {
            return 1;
        }
    }

    for (int i = col + 1; i < forest[row].size(); i++)
    {
        if (forest[row][i] >= tree)
        {
            return 0;
        }

        else if (i == forest[row].size() - 1)
        {
            return 1;
        }
    }

    return 10000;

}

int findedgesums(vector<vector<int>> forest)
{
    int toptotal;
    toptotal = forest[0].size()*2;

    int sidetotal;
    sidetotal = forest.size() * 2 - 4; 


    return (sidetotal + toptotal);
}

// worlds most inefficient code holy
void part1()
{
    vector<vector<int>> forest;
    getinput(forest);

    int total = 0;

    // count interior
    for (int i = 1; i < forest.size()-1; i++)
    {
        for (int j = 1; j < forest[i].size()-1; j++)
        {
            total += checktree(forest, forest[i][j], i, j);
        }
    }

    total += findedgesums(forest);

    cout << total;
}



void calculatescore(const vector<vector<int>> &forest, int row, int col, int tree, int &highscore)
{
    int onetree = 1;
    int onedirection = 0;

    //look up
    for (int i = row - 1; i >= 0; i--)
    {
        onedirection++;
        if (forest[i][col] >= tree)
        {
            break;
        }
    }
    onetree *= onedirection;
    onedirection = 0;

    // look down
    for (int i = row + 1; i < forest.size(); i++)
    {
        onedirection++;
        if (forest[i][col] >= tree)
        {
            break;
        }
    }

    onetree *= onedirection;
    onedirection = 0;

    // look left
    for (int i = col - 1; i >= 0; i--)
    {
        onedirection++;
        if (forest[row][i] >= tree)
        {
            break;
        }
    }
    onetree *= onedirection;
    onedirection = 0;

    // look right
    for (int i = col + 1; i < forest[row].size(); i++)
    {
        onedirection++;
        if (forest[row][i] >= tree)
        {
            break;
        }
    }
    onetree *= onedirection;

    if (onetree > highscore)
    {
        highscore = onetree;
    }
    
    // something s wrong with the postcrement
    // precrement things
}


void part2()
{
    vector<vector<int>> forest;
    getinput(forest);

    int highscore = 0;

    for (int i = 1; i < forest.size() - 1; i++)
    {
        for (int j = 1; j < forest[i].size() - 1; j++)
        {
            calculatescore(forest, i, j, forest[i][j], highscore);
        }
    }

    cout << highscore;
}
int main()
{
    part1();

    part2();

    return 0;
}   
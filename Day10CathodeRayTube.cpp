#include <iostream>
#include <vector>


using namespace std;

struct command
{
    string name;
    int value;
    int cyclevalue;
};

int abs(int a)
{
    if (a < 0)
    {
        return -a;
    }

    else return a;
}

void getInput(vector<command> &c)
{
    command temp;
    
    while (cin >> temp.name)
    {
        if (temp.name == "addx")
        {
            cin >> temp.value;
            temp.cyclevalue = 2;
        }

        // if temp.name == noop
        else
        {   
            temp.value = 0;
            temp.cyclevalue = 1;
        }

        c.push_back(temp);
    }
}

bool correctcycle(int cycle)
{
    return (cycle % 40 == 20);
}

void processcycle1(int cyclenum, int &cycle, int &regist, int &sigstr)
{
    // create a cycle loop
    for (int j = 0; j < cyclenum; j++)
    {  
        cycle++;
        if (correctcycle(cycle))
        {
            sigstr += regist * cycle;
        }
    }
}

void part1()
{
    vector<command> commands;
    getInput(commands);
    

    int cycle = 0, regist = 1, sigstr = 0;

    // loop through the command list
    for (int i = 0; i < commands.size(); i++)
    {
        processcycle1(commands[i].cyclevalue, cycle, regist, sigstr);
        
        regist += commands[i].value;
    }
    


    cout << sigstr;
}

char** createimage()
{
    char **x = new char* [6];
    for (int i = 0; i < 6; i++)
    {
        x[i] = new char[40];
        for (int j = 0 ; j < 40; j++)
        {
            x[i][j] = '.';
        }
    }

    return x;
}

void updateimage(char** image, int row, int col, int spritepos)
{
    if (abs(spritepos - col) <= 1)
    {
        image[row][col] = '#';
    }
}

void outputimage(char **image)
{
    for(int row = 0; row < 6; row++)
    {
        for (int col = 0; col < 40; col++)
        {
            cout << image[row][col];
        }
        cout << endl;
    }
}

void part2()
{
    // getting input
    vector<command> commands;
    getInput(commands);

    // 2d array that holds our image
    char** image = createimage();

    //cycle holds the position of the beam 0 < cycle < 239
    //regist holds the position of the sprite
    int cycle = 0, regist = 1;
    for (int i = 0; i < commands.size(); i++)
    {   
        // delay the update of the sprite 
        for (int j = 0; j < commands[i].cyclevalue; j++)
        {
            updateimage(image, cycle / 40, cycle % 40, regist);
            cycle++;
            cycle %= 240;
        }

        // update sprite
        regist += commands[i].value;
    }
    

    outputimage(image);
}

int main()
{
    //part1();

    part2();
    return 0;
}
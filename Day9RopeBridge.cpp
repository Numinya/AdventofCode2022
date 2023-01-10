#include <iostream>
#include <vector>
#include <cmath>


using namespace std;

struct command
{
    char direction;
    int magnitude;

    command() {}

    command(char d, int m)
    {
        direction = d;
        magnitude = m;
    }

    void reset()
    {
        magnitude = 0;
    }
};

struct coordinate
{
    int x;
    int y;
    coordinate *nextnode = NULL;
    

    coordinate()
    {
        x = 0;
        y = 0;
    }

    coordinate(int a,  int b)
    {
        x = a;
        y = b;
        nextnode = NULL;
    }

    bool operator == (const coordinate &a)
    {
        return (a.x == x && a.y == y);
    }

    coordinate operator + (const coordinate &a)
    {
        coordinate temp;
        temp.x = x + a.x;
        temp.y = y + a.y;
        
        return temp;
    }

    coordinate operator - (const coordinate &a)
    {
        coordinate temp;
        temp.x = x - a.x;
        temp.y = y - a.y;

        return temp;
    }

    void operator= (const coordinate & a)
    {
        x = a.x;
        y = a.y;
    }


    
};



// takes initial input from terminal
void getInput(vector<command> &v)
{
    command temp;
   
    while(cin >> temp.direction)
    {
        cin >> temp.magnitude;
        
        v.push_back(temp);
    }
}

// ------------------- part 1 ----------------------------------

// checks if a point exists in a linked list
void exists(coordinate *list, coordinate *point)
{
    coordinate *head = list;
    coordinate *last;

    bool exist = false;
    while (list != NULL)
    {
        if (*point == *list)
        {
            exist  = true;
            break;
        }

        last = list;
        list = list->nextnode;
    }

    if (!exist)
    {
        last->nextnode = point; 
        point->nextnode = NULL;
    }

    else
    {
        delete point;
    }
}

// --------- add position functinos -------------
void addpositionsu(coordinate *list, const coordinate &point, int start, int end)
{

    for (int i = start; i < end; i++)
    {
        coordinate *sum = new coordinate(point.x, i); 
        exists(list, sum);
    }
}
void addpositionsd(coordinate *list, const coordinate &point, int start, int end)
{
   
    
    for (int i = start; i > end; i--)
    {
        coordinate *sum = new coordinate(point.x, i);
        exists(list, sum);
    }
}
void addpositionsl(coordinate *list, const coordinate &point, int start, int end)
{
  
    
    for (int i = start; i > end; i--) //suspect the start end bounds are wrong
    {
        coordinate *sum = new coordinate(i, point.y);
        exists(list, sum);
    }
}
void addpositionsr(coordinate *list, const coordinate &point, int start, int end)
{
    for (int i = start; i < end; i++)
    {
        coordinate *sum = new coordinate(i, point.y);
        exists(list, sum);
    }
}

// counts the elements in a linked list
int countlist(coordinate *list)
{
    int total = 1;
    while(list->nextnode != NULL)
    {
        total++;

        list = list->nextnode;
    }

    return total;
}

void part1(const vector<command> &commands)
{
    coordinate head(0, 0);
    coordinate first(0 ,0);
    coordinate *list = &first;

    //  tracks the distance the head away from tail -1 < x < 1
    int tailx = 0;
    int taily = 0;

    // loop through all the commands
    for (int i = 0; i < commands.size(); i++)
    {
        switch (commands[i].direction)
        {
        case 'U':
            // if the movement takes it outside the range
            if (abs(taily + commands[i].magnitude) > 1)
            {
                addpositionsu(list, head, head.y + (1 - taily), 
                              head.y + commands[i].magnitude);

                head.y += commands[i].magnitude;

                tailx = 0;
                taily = 1;                 
            }

            // |magnitude - y| <= 1
            else 
            {
                head.y += commands[i].magnitude;
                taily += commands[i].magnitude;
            }
        
            break;

        case 'D':
            if (abs(taily - commands[i].magnitude) > 1)
            {
                addpositionsd(list, head, head.y - (1 + taily), 
                              head.y - commands[i].magnitude);

                head.y -= commands[i].magnitude;

                tailx = 0;
                taily = -1;
            }

            else 
            {
                head.y -= commands[i].magnitude;
                taily -= commands[i].magnitude;
            }
            break;
        
        case 'L':
            if (abs(tailx - commands[i].magnitude) > 1)
            {
                addpositionsl(list, head, head.x - (1 + tailx), 
                              head.x - commands[i].magnitude);

                head.x -= commands[i].magnitude;

                tailx = -1;
                taily = 0;
            }

            else 
            {
                head.x -= commands[i].magnitude;
                tailx -= commands[i].magnitude;
            } 
            break;

        // case 'R'
        default:
            if (abs(tailx + commands[i].magnitude) > 1)
            {
                addpositionsr(list, head, head.x + (1 - tailx), 
                              head.x + commands[i].magnitude );

                head.x += commands[i].magnitude;

                tailx = 1;
                taily = 0; 
            }

            else 
            {
                head.x += commands[i].magnitude;
                tailx += commands[i].magnitude;
            }
            break;
        }

        cout << countlist(list);
    }

    // output
    cout << countlist(list);
}
//---------------------------------------------------------------

// ------------------ part 2 ---------------------------------------------------

bool headnotinrange(const coordinate &head, const coordinate &tail)
{
    return(abs(head.x - tail.x) > 1 || abs(head.y - tail.y) > 1);
}

// translates a command (char, int) into a coordinate (int, int)
coordinate translatecommand(char c)
{
    switch(c)
    {
        case 'U':
            return coordinate(0, 1);
            
        case 'D':
            return coordinate(0 ,-1);

        case 'R':
            return coordinate(1, 0);

        default:
            return coordinate (-1, 0);

    }
}

// creates a linked list (for some practise)
void createtaillist(coordinate *&head, coordinate *&tail)
{
    coordinate *item = new coordinate(0,0);
    head = item;


    for(int i = 0; i < 9; i++)
    {
        coordinate *temp = new coordinate(0,0);
        item->nextnode = temp;
        item = temp;
    }

    tail = item;
}

// checks if point exists in visited and adds it to visited vector
void addcoordinate(vector<coordinate> &visited, const coordinate &point)
{
    bool exists = false;
    for (int i = 0; i < visited.size(); i++)
    {
        if (visited[i] == point)
        {
            exists = true;
            break;
        }
    }

    if (!exists)
    {
        visited.push_back(point);
    }
}

// moves the head in the correct direction
void movehead(coordinate *head, const coordinate &oneunit, coordinate &oldhead)
{
    oldhead = *head;
    *head = *head + oneunit;
}

int calcmove(int a)
{
    return (a > 0? 1: (a == 0? 0: -1));
}


coordinate& createmove( coordinate &head,  coordinate &tail)
{   
    coordinate *temp = new coordinate;
    *temp = head - tail;
    temp->x = calcmove(temp->x);
    temp->y = calcmove(temp->y);
    

    return *temp;
}

void movetails(coordinate *&head, coordinate &oldpos)
{
    coordinate *movetail = head;
    
    coordinate move;
    
    for(int i = 0; i < 9; i++)
    {
          

        if (headnotinrange(*movetail, *(movetail->nextnode)))
        {
            move = createmove(*movetail, *(movetail->nextnode));

            *(movetail->nextnode) = *(movetail->nextnode) + move; 


            movetail = movetail->nextnode;
        }

        else break;
    }
    
    
}


void part2()
{
    vector<command> commands;   
    getInput(commands);
    
    
    vector<coordinate> visited;

   /* head - points to the very first node
      tail - points to the very last node
      oldhead - is the position that the head used to be
      oneunit - is a command converted to a coordinate */
   
    coordinate *head, *tail;
    coordinate oldhead, oneunit;
    createtaillist(head, tail);
    



    for(int i = 0; i < commands.size(); i++)
    {
        oneunit = translatecommand(commands[i].direction);

        for (int j = 0; j < commands[i].magnitude; j++)
        {
            movehead(head, oneunit, oldhead);

            movetails(head, oldhead);

            
        
            // add the point to the list
            addcoordinate(visited, *tail);
        }
    }

    

    cout << visited.size();
}


int main()
{
    /* ----- part 1 --------
    vector<command> commands;
    getInput(commands);
    part1(commands);
    ---------------------- */

    part2();


    return 0;
}
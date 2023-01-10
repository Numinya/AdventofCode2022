#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct directory
{
    //data
    string name;
    vector<int> files;
    vector<directory *>  children;
    directory *parent = NULL;

    
    directory ()
    {}

    directory (string dirname, directory *level)
    {
        name = dirname;
        parent = level;
    }

    int sumfilesize()
    {
        int size = 0;
        
        // add its own files
        for (int i = 0; i < files.size(); i++)
        {
            size += files[i];
        }

        // add all its childrens files
        for (int i = 0; i < children.size(); i++)
        {
            size += children[i]->sumfilesize();
        }

        return size;
    }

};

// seraches for dirname in the currentfiles 
directory *search(string dirname, directory *currentfile)
{
    for (int i = 0; i < currentfile->children.size(); i++)
    {
        if (dirname == (currentfile->children)[i]->name)
        {
            return (currentfile->children)[i];
        }
    }
    
    return currentfile; // this is here so theres no yellow error, it works perfectly fine
}


// something that goes in setuptree(), 
// just to setup a root node
directory *createrootnode()
{
    directory *temp = new directory;
    string command;
    for (int i = 0; i < 3; i++)
    {
        cin >> command;
        if (i == 2)
        {
            temp->name = command;
        }
    }

    return temp;
}


// takes the input and creates a general tree
directory *setuptree()
{
    string command;
    string dirname;
    string secondcommand;
    int filesize;

   
    directory *level = createrootnode();
    directory *base = level;


    // tree setup
    while(cin >> command)
    {

        if (command == "cd")
        {
            // something about 
                                   
            cin >> dirname; 
             // this runs even when its ".."

            if (dirname == "..")
            {
                // move reference level up one
                level = level->parent; 
            }

            else 
            {
                level = search(dirname, level);
            }
        }

        else if (command == "ls")
        {
            while(cin >> secondcommand)
            {
                // check end of the $ ls command
                if (secondcommand == "$")
                {
                    break;
                }

                // if listed thing is a directory
                else if (secondcommand == "dir")
                {
                    cin >> dirname;
                    level->children.push_back(new directory(dirname, level));
                }

                // if listed thing is a file
                else
                {
                    level->files.push_back(stoi(secondcommand));
                    cin >> dirname;
                }

            }
        }
    }

    return base;
}


// function for part 1
int addrequired (directory *node)
{
    int total = 0;
    int filesize = node->sumfilesize();
    if (filesize <= 100000)
    {
        total += filesize;
    }

    for (int i = 0; i < node->children.size(); i++)
    {
        total += addrequired(node->children[i]);
    }

    return total;
}

void part1()
{
    directory *root = setuptree();

    cout << addrequired(root);   

    delete root; 
}



// function for part 2
int findsmallest (directory *node, int availible, int smallfile)
{
    int filesize = node->sumfilesize();
    if (availible + filesize > 30000000 && filesize < smallfile)
    {
            smallfile = filesize;
    }

    for (int i = 0; i < node->children.size(); i++)
    {
        
        smallfile = findsmallest(node->children[i], availible, smallfile); 
    }

    return smallfile; 
}


void part2()
{
    directory *root = setuptree();
    int used = root->sumfilesize();
    int unused =  70000000 - used;
    int smallfile = used;

    cout << findsmallest(root, unused, smallfile);


    delete root;
}

int main()
{
    part1();

    part2();

    return 0;
}
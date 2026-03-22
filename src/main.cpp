#include "AVLTree.h"
#include <iostream>
#include <sstream>
using namespace std;

int main()
{
    // create tree instance
    AVLTree tree;
    // get first line of input (number of commands)
    int numCommands;
    cin >> numCommands;
    cin.ignore();
    string oneLineOfInput, command;

    for(int i = 0; i < numCommands; i++)
    {
        getline(cin, oneLineOfInput);
        istringstream in(oneLineOfInput);

        // get first argument in line (actual command name)
        getline(in, command, ' ');

        // check command and perform operations as necessary
        if(command == "insert")
        {
            string name;
            getline(in, name, '"');
            getline(in, name, '"');
            string ufid;
            in >> ufid;
            if(tree.nameCheck(name) != "ERROR" && tree.idCheck(ufid) != "ERROR")
            {
                tree.insertNameID(name, ufid);
            }
            else cout << "unsuccessful" << endl;
        }

        else if(command == "remove")
        {
            string ufid;
            getline(in, ufid);
            if(tree.idCheck(ufid) == "ERROR") cout << "unsuccessful" << endl;
            else
            {
                tree.removeID(ufid);
            }
        }

        // this shit is kicking my ass lowkey...
        else if(command == "search")
        {
            string restOfInputLine;
            getline(in, restOfInputLine);

            if (restOfInputLine.empty()) cout << "unsuccessful" << endl;
            if(restOfInputLine.front() == '"') {

                restOfInputLine = restOfInputLine.substr(1);
                restOfInputLine.pop_back();
                if(tree.nameCheck(restOfInputLine) != "ERROR") tree.searchName(restOfInputLine);
                else cout << "unsuccessful" << endl;
            }
            else{
                if(tree.idCheck(restOfInputLine) != "ERROR") tree.searchID(restOfInputLine);
                else cout << "unsuccessful" << endl;
            }
        }

        else if(command == "printInorder")
        {
            tree.printInOrder();
            cout << endl;
        }

        else if(command == "printPreorder")
        {
            tree.printPreOrder();
            cout << endl;
        }

        else if(command == "printPostorder")
        {
            tree.printPostOrder();
            cout << endl;
        }

        else if(command == "printLevelCount") tree.printLevelCount();

        else if(command =="removeInorder")
        {
            string n;
            getline(in, n);
            if(tree.isDigit(n))
            {
                int n2 = stoi(n);
                tree.removeInOrder(n2);
            }
                // edited this 7:19pm
            else cout << "unsuccessful" << endl;
        }
        else cout << "not a valid command" << endl;
    }
    return 0;
}

//Deletion part of RBT, title file, Colin Aslett C++ Period 07 
#include <iostream>
#include "rbt.h"
#include <fstream>

using namespace std;

void populate(RedBlackTree &redBlackTree, char *list);
void addFromInput(RedBlackTree &redBlackTree);//adding via manually
bool addFromFile(RedBlackTree &redBlackTree);//adding via file


int main(){
    while(true){
        RedBlackTree redBlackTree;
        char input;
        cout << "Choose an option: 1 Enter numbers manually, 2 Enter file name ,3 Quit program." << endl;
        cin >> input;
        if(input == '1'){//adding numbers manually
            addFromInput(redBlackTree);
        }
        else if(input == '2'){//adding numbers via file
            if(!addFromFile(redBlackTree)){//Could not open the file
                continue;
            }
        }
        else if (input == 'q'){//quits
            break;
        }
        else{
            cout << "Command not recognized." << endl;
            continue;
        }
        
        while(true){
            cout << "Several Options: 1 Print out the tree, 2 Add number(s), 3 Add numbers from a file, 4 Start a new tree, 5 Check if a number is in the tree, 6 Remove a number from the tree, q Quit program" << endl;
            cin >> input;
            if(input == '1'){//printing out the tree
                cout << "Tree:" << endl;
                redBlackTree.print();
            }
            else if (input == '2'){//adding via manually
                addFromInput(redBlackTree);
            }
            else if (input == '3'){//adding via file
                addFromFile(redBlackTree);
            }
            else if (input == '4' || input == 'q'){
                break;
            }
            else if(input == '5'){
                int num;
                cout << "Enter your number: ";
                cin >> num;
                if(redBlackTree.isInTree(num)){
                    cout << "Number found" << endl;
                }
                else{
                    cout << "Your number" << endl;
                }
            }
            else if(input == '6'){
                int num;
                cout << "Enter the number to remove: ";
                cin >> num;
                if(redBlackTree.remove(num)){
                    cout << "Number removed successfully." << endl;
                }
                else{
                    cout << "Number not found in the tree." << endl;
                }
            }
            else{
                cout << "???" << endl;
            }
            cout << "Press enter to continue." << endl;
            cin.ignore();
            cin.get();
        }
        if(input == 'q'){
            break;
        }
        
    }
    return 0;
}
//popualting tree 
void populate(RedBlackTree &redBlackTree, char *list){
    int index = 0;
    while(list[index]){
        if(isdigit(list[index])){
            int num = list[index] - '0';
            while(isdigit(list[++index])){
                num = 10*num + (list[index] - '0');
            }
            redBlackTree.insert(num);
        }
        else{
            index++;
        }
    }
}
//adding numbers manually
void addFromInput(RedBlackTree &redBlackTree){
    char list[150];
    cout << "Enter the numbers, separated by commas and/or spaces:" << endl;
    cin.ignore();
    cin.getline(list, 150);
    populate(redBlackTree, list);
}
//adding numbers via a file
bool addFromFile(RedBlackTree &redBlackTree){
    char filename[32];
    cout << "Enter the file name: ";
    cin >> filename;
    ifstream stream(filename);
    if(stream.is_open()){
        char list[16384];
        stream.getline(list, 16384, 0);
        stream.close();
        populate(redBlackTree, list);
        return true;
    }
    else{
        cout << "Could not open file." << endl;
        return false;
    }
}

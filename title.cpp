//Deletion part of RBT, title file, Colin Aslett C++ Period 07 
#include <iostream>
#include <fstream>
#include "rbt.h"
using namespace std;

int main(){
  while(true){
    char input;
    cout << "Welcome to RBT add+deletion you have 3 options, 1 = add manually, 2 = add via file, q = quit :(" << endl;
    cin >> input;
    if(input == '1'){
      //add number manually
    }
    else if(input == '2'){
      //add number via file
    }
    else if(input == 'q'){
      break;//quits
    }
    //if you entered something that is not one of the listed options
    else{
      continue;
    }
    //You gain more options once you have added numbers
    while(true){
      cout << "6 options, 1 = add manually, 2 = add via file, 3 = print out tree, 4 = search for number, 5 = remove number from tree, q = quit" << endl;
      cin >> input;
      if(input == '1'){
	//add numbers manually
      }
      else if(input == '2'){
	//add numbers via file
      }
      else if(input == '3'){
	//print out tree
      }
      else if(input == '4'){
	//searching for a number
	int x;
	cout << "enter number: " << endl;
	cin >> x;
	//search the tree for your number
      }
      else if(input == '5'){
	int xx;
	cout << "enter a number to delete: " << endl;
	cin >> xx;
	//remove the number from the tree
      }
      else if(input == 'q'){
	break;
      }
      else{
	//user inputted invalid command
	cout << "invalid command request" << endl;
      }
      cout << "Press enter to continue" << endl;
      cin.ignore();
      cin.get();
    }
    if(input == 'q'){
      break;
    }
  }
  return 0;
}

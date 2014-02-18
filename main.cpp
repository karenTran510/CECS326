//      Karen Tran
//      CECS326, Section 1
//      Lab 1: Programming Review

//      Program Description: The first lab is a "Program Review" of C++. The program is required to initialize
//      an integer array and a character array of pointers.
//      Both arrays have a size of 20 elements. Each element in the integer array is a value multiplied by 2,
//      where the starting value is 2900. Each pointer, in the character pointer array, points to another character array.
//      The character array is initialized to a size, retrieved from each element in the integer array. When the program's
//      main function runs, the user has the option of displaying 10 characters from the pointer array, deleting the pointer's
//      reference, or exiting the program.
// Error fixed: Segmentation faults ensued because the char pointer wasn't deleted correctly in the third case of the switch statement in the
// main function. The char pointer was an array of pointers, which meant, the entire array must be deleted.

#include<cstdlib>
#include<stdlib.h>
#include<stdio.h>
#include <iostream>
#include<string>
#include<sstream>
using namespace std;

//A class with two attributes, int array and pointer char array
struct Memory {
    int numArray[20];
    char * pointers[20];
}obj;

//****************Methods******************//

//Initialize integer array
void initNum(int n_ray[]){
    //numStart will be used to increment size of arrays
    int numStart = 1;
    //Set the first element of the int array as numStart
    n_ray[0] = numStart;
    //Multiply each following element with numStart and 2
    for (int i = 1; i < 20; i++)
    {
        n_ray[i] = 2*n_ray[i-1];
    }
}

//Returns random letters from the alphabet
char randomChar() {
    //Store all letters in an array, "alphabet"
    char alphabet[26] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N',
            'O','P','Q','R','S','T','U','V','W','X','Y','Z'};
    //Random number generator that outputs a number from 0 - 26
    int i = rand()%26;
    //The number will reference the location of the letter, and will be returned
    return alphabet[i];
}

//Creates a new char array, and its size is based on numArray values
char* newCharArray(int n_ray[], int counter){
    //Takes in counter to determine size for new_char
    int size = n_ray[counter];
    char* new_char = new char [size];

    //Fill in random letters in new char array
    for (int j = 0; j < size; j++){
        new_char[j] = randomChar();
    }

    return new_char;
}

//Initializes the Pointer array by pointing to newly created char arrays
void initPointer(char * cArray[], int n_ray[])
{
    //Have each element point to an array
    for (int i = 0; i < 20; i++){
        cArray[i] = newCharArray(n_ray, i);
    }
}

//Prints out 10 characters starting from the given index
void display10 (char ** pointer, int n_ray [], int point_index,int index){

    //Check if the pointer is empty
    if (pointer[point_index] != NULL)
    {
        //Printing out  10 characters
        for(int i = index; i < index+10 && i < n_ray[point_index]; i++)
        {
            cout << i << ": " << pointer[point_index] [i]<< endl; // print out the letter at that location
        }
    }

    //Else, print out the 10 characters
    //"pointer" will be used to search through the pointed char array by adding the address at the index
        //then, incrementing the pointer by one until 10 characters are printed out
    if (pointer[point_index] == NULL){
        cout << "it was nulled"<<endl;
       cout << "The pointer at this index was deleted."<< endl;
       pointer[point_index] = newCharArray(n_ray, point_index);
        cout << "A new array has been created." << endl;
    }
}



//*******************Main function*********************//
int main() {
    //Initialize the two struct attributes
    initNum(obj.numArray);
    cout << "Initializing...."<<endl;
    initPointer(obj.pointers, obj.numArray);
    cout << "Initialization complete" <<endl;

    //Declare variables that will store user's input
    int input = 0;
    int input_2;
    //Stores the position in char * pointers [] the user entered
    int point_index;

    //Repeatedly run until the user wishes to quit
    while(input!=2){
        //Print out the startup menu
    cout << "Main Menu"<< endl;
    cout << "(1) Accessing a Pointer" << endl;
    cout << "(2) Exit program" << endl;
    cin >> input;

    //Submenu if user chose 1
    if(input == 1)
    {
        cout << "Enter an index from character array." << endl;
        cin >> point_index;
        cout << "Pointer menu" << endl;
        cout << "(1) Display 10 characters" << endl;
        cout << "(2) Delete a character at a specific index "<< endl;
        cout << "(3) Return to Main Menu"<< endl;
        cin >> input_2;

        //Three cases based on user's input in submenu
        switch(input_2)
        {
            int index;
            //Display the 10 characters of the pointed char array
            case 1: cout << "Enter an index to display 10 characters."<<endl ;
                    cin >> index;
                    cout << "gonna display" << endl;
                    display10(obj.pointers,obj.numArray,point_index,index);
                    break;
            //Delete the pointer
            case 2: cout << "Array deleted."<< endl;
                    delete[] obj.pointers[point_index];
                    obj.pointers[point_index] = NULL;
                    break;
            //Pull up the Main Menu
            case 3:
            break;
        }
    }

    }
//If the user chooses 2, then the program exits the while loop
 cout << "Goodbye!";
 //Checks if the pointers array has been deleted after the main function finishes
 for(int i = 0; i < 20; i ++)
 {
     if(obj.pointers[i] != NULL)
     delete[] obj.pointers[i];
 }
};

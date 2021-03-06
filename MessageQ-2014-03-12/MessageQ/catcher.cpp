#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <cstring>
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <cstdlib>
#include <string.h>
#include <sstream>
#include "randgen.h"
using namespace std;

int main() {
    
    int qid = msgget(ftok(".",'u'), 0); //Get the ID of the queue from the banner program
    init(); //Initialize randgen.o 

    // Declare message buffer for catcher
    struct buf {
        long mtype; // required
        char greeting[50]; // message content
    };
    buf msg;
    int size = sizeof(msg)-sizeof(long);
     

    //Variables used in the while-loop
    stringstream convert; // stringstream used for the conversion
    int randNum = randgen(qid); 
    int prime = 11; 
    //Stores randNum and prime as type 'char'
    const char* r;
    const char* p;
    //Stores randNum and prime as type 'string'
    string rand_str;
    string prime_str;
    //The result from the divisibility check is stored in notify
    int notify; 
    
    //Converts the prime into type 'string'
    convert << prime; 
    prime_str = "    Prime Number: " + convert.str();
    //prime_str is converted into type 'char' and stored in 'p' 
    p = prime_str.c_str(); 
  
    cout << "Catcher_1 is beginning..." << endl; 	
    /*Catcher_1 will continue to loop until randNum is less than 100
     *If randNum is less than zero, it will divide it by prime (11),
     * and send the numbers to banner after converting it to type 'char'*/
    while(randNum > 100) {

        notify = randNum%prime;

        if(notify == 0) {    
            //Set mtype
            msg.mtype=21;
	    //Clear stringstream
	    convert.str("");
	    convert.clear();
	    //Convert random number		    
	    convert << randNum; //add the value of num to the characters in the stream
	    //Store the converted randomNum into a 'string' variable
	    rand_str = "Random Number: " + convert.str(); 
	    //rand_str is converted into type 'char' and store in 'r'
            r = rand_str.c_str();
           
            //Add the randNum and prime as char to msgQ
            strcpy(msg.greeting, r);
	    //Attach the prime number into the message
	    strcat(msg.greeting, p); 
            //Send randNum and prime to banner
            msgsnd(qid, (struct msgbuf *)&msg, size, 0);
	    cout << "Catcher_1 sent a message" << endl;
        }
        //Else, generate another randNum and prime, and start at the top
        randNum = randgen(qid);      
    }    
    //Sends banner a notification that it's exiting
    msg.mtype=13; 
    strcpy(msg.greeting, "Catcher_1 is now exiting. Goodbye~");
    msgsnd(qid,(struct msgbuf *)&msg, size,0); 

    //Catcher_1 exits
    exit(0);  
};

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
    const char* r;
    const char* p;
    string rand_str;
    string prime_str;
    int notify; 
    
    convert << prime; 
    prime_str = "    Prime Number: " + convert.str();
    p = prime_str.c_str(); 
  
    cout << "Catcher_2 is beginning..." << endl; 	
    //Will continue to loop until randNum is less than 100    
    while(randNum > 100) {

        notify = randNum%prime;

        if(notify == 0) {    
            //Set mtype
            msg.mtype=22;
	    //Clear stringstream
	    convert.str("");
	    convert.clear();
	
	    //Convert random number		    
	    convert << randNum; //add the value of num to the characters in the stream
	    rand_str = "Random Number: " + convert.str();//return content of stream 
            r = rand_str.c_str();
           
            //Add the randNum and prime as char to msgQ
            strcpy(msg.greeting, r);
	    strcat(msg.greeting, p);
            //Send randNum and prime to banner
            msgsnd(qid, (struct msgbuf *)&msg, size, 0);
	    cout << "Catcher_2 sent a message" << endl;
        }
        //Else, generate another randNum and prime, and start at the top
        randNum = randgen(qid);      
    }    
    //Send banner a notification that it's exiting
    msg.mtype=13; 
    strcpy(msg.greeting, "Catcher_2 is now exiting. Goodbye~");
    msgsnd(qid,(struct msgbuf *)&msg, size,0); 

    //Catcher_2 exits
    exit(0);  
};

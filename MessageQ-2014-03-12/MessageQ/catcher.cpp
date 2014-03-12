#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <cstring>
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <cstdlib>
#include "randgen.h"
using namespace std;

int main() {
	
	
	double notify; //Test if notify is 0
	int qid = msgget(ftok(".",'u'), 0); //Initialize queue
	init();//Initialize randgen.o 

	// Declare message buffer
	struct buf {
		long mtype; // required
		char greeting[50]; // mesg content
	};
	buf msg;
	int size = sizeof(msg)-sizeof(long);

	//Generate randon number
	int randNum = randgen(qid); 
	
	//Will continue to loop until randNum is less than 100	
	while(randNum > 100) {
		//Generate prime number
		int prime; 
		notify = randNum%prime;

		if(notify == 0) {	
			//Set mtype
			//Send randNum and prime to banner
		}
	}	
	
	//Exit catcher
	exit(0);  
};




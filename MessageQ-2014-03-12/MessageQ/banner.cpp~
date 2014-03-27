//	Karen Tran
//	CECS 326, Section 1
//	Project 2: Message Queue
//	Files included: randgen.o, randgen.h, catcher.cpp, catcher2.cpp, catcher3.cpp
//	Project Description: The banner receives messages from all three catchers. 
//	The banner will filter out the "fake" messages sent by randgen. It will check for
//	the mtype of each message it receives, and only displays the message with the right
// 	mtype. The catcher's exiting message will have an mtype of 13. Every occurence of 
//	mytpe=13, the banner will decrement its catcher_counter until it reaches 0. 
 
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <cstring>
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <cstdlib>
using namespace std;

int main() {

	// Create Message Queue with key value from ftok()
	int qid = msgget(ftok(".",'u'), IPC_EXCL|IPC_CREAT|0600);

	// Declare message buffer
	struct buf {
	long mtype; // required
	char greeting[50]; // mesg content
	};
	buf msg; //Message buffer
	int size = sizeof(msg)-sizeof(long);
	//Keeps track of how many catchers have exit the program
	int catcher_counter = 3;	
	
	/*The banner will continually check for the right mtypes from the catcher.
	 *It will display the random number and prime number of messages with matching mtypes.
	 *When a catcher exits, it will attach a "Goodbye" to the message.*/
	cout << "Banner is beginning..." << endl;
	while(catcher_counter!=0) {
		//Receives the message from top of queue
		msgrcv(qid, (struct msgbuf *)&msg, size, 0, 0);
		
		if(msg.mtype==21) {
			//Display the event catcher
			cout << "Catcher c1: " << getpid() << endl;
			//Display the Random number and Prime 
			cout << msg.greeting << endl; 
		}
		else if(msg.mtype==22) { 
			//Display the event catcher
			cout << "Catcher c2: " << getpid() << endl;
			//Display the Random number and Prime 
			cout << msg.greeting << endl;		
		}
		else if(msg.mtype==23) { 
			//Display the event catcher
			cout << "Catcher c3: " << getpid() << endl;
			//Display the Random number and Prime 
			cout << msg.greeting << endl;
		
		}
		//If a catcher exits, the banner will attach a goodbye
		else if(msg.mtype==13) {
			cout << msg.greeting<< endl;
			strcat(msg.greeting, " Goodbye Catcher~");
			catcher_counter--; 
		}			
		
	}

	//The banner has completed displaying all of the catcher's messages
	cout << "Banner is now closing. Goodbye~" << endl; 
	//Delete message queue
	msgctl (qid, IPC_RMID, NULL);
 
}


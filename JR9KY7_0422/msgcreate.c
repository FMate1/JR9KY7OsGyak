#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdlib.h>
#define MSGKEY 654321L

struct msgbuf1 {

	long mtype;
	char mtext[512];

} sndbuf, *msgp;		// Üzenet buffer és pointere



int main()
{
	int msgid;		// Üzenetsor azonosító
	key_t key;		// Kulcs az üzenetsorhoz
	int msgflg;		// flag a kreáciohoz, üzenetküldéshez
	int rtn, msgsz;		// return es méret

	key = MSGKEY;
	msgflg = 00666 | IPC_CREAT;
	msgid = msgget( key, msgflg);
 	if ( msgid == -1) {
                perror("\n Az msgget rendszerhívás sikertelen!");
                exit(-1);
        }
	printf("\n Az msgid %d, %x : ", msgid, msgid);




	msgp = &sndbuf;
	msgp->mtype = 1;   			// Text típus
 	strcpy(msgp->mtext,"Az egyik üzenet");
	msgsz = strlen(msgp->mtext) + 1;	// Az üzenet hossza




    rtn = msgsnd(msgid,(struct msgbuf *) msgp, msgsz, msgflg);
	printf("\n Az 1. msgsnd visszaadott %d-t", rtn);
	printf("\n A kiküldött üzenet: %s", msgp->mtext);


	strcpy(msgp->mtext,"Másik üzenet");
	msgsz = strlen(msgp->mtext) + 1;
	rtn = msgsnd(msgid,(struct msgbuf *) msgp, msgsz, msgflg);
	printf("\n A 2.  msgsnd visszaadott %d-t", rtn);
	printf("\n A kiküldött üzenet: %s \n", msgp->mtext);

	exit (0);
}

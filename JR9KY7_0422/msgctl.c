#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdlib.h>
#define MSGKEY 654321L

int main()
{
	int msgid, msgflg,  rtn;
	key_t kulcs;
	kulcs = MSGKEY;
	msgflg = 00666 | IPC_CREAT;
	msgid = msgget(kulcs, msgflg);

	rtn = msgctl(msgid, IPC_RMID, NULL);	// T�rl�m az �zenetsort
	printf ("\n Visszt�rt: %d", rtn);

	exit (0);
}

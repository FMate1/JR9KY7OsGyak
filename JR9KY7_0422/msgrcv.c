#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdlib.h>
#define MSGKEY 654321L

struct msgbuf1 {

	long tipus;
	char mtext[512];

} rcvbuf, *msgp;		// Message buffer es pointere

struct msqid_ds ds, *buf;	// �zenetsorhoz asszocialt struktura �s pointere

int main()
{
	int msgid;		// �zenetsor azonos�t� ID
	key_t kulcs;		// Kulcs az �zenetsorhoz
	int tipus, msgflg;	// T�pus, flag
	int rtn, meret;		// return es m�ret

	kulcs = MSGKEY;		// Be�ll�tom a kulcsot
	msgflg = 00666 | IPC_CREAT | MSG_NOERROR;

	msgid = msgget(kulcs, msgflg);
 	if ( msgid == -1) {
                perror("\n Az msgget rendszerh�v�s sikertelen!");
                exit(-1);
        }
	printf("\n Az �zenet ID: %d",msgid);

	msgp = &rcvbuf;		// �zenetfogad� buffer
	buf = &ds;		// �zenetsor jellemz� adataihoz
	meret = 20;		// Max hossz
	tipus = 0;		// Minden t�pust v�rok
	rtn = msgctl(msgid,IPC_STAT,buf); // �zenetsor adatokat lekerdezem
	printf("\n Az uzenetek szama: %ld",buf->msg_qnum);

	while (buf->msg_qnum) {		// Van-e uzenet?


    // Veszem a k�vetkez� �zenetet:
	rtn = msgrcv(msgid,(struct msgbuf *)msgp, meret, tipus, msgflg);
	printf("\n Visszat�r�s: %d, A fogadott �zenet:%s\n",rtn, msgp->mtext);
	rtn = msgctl(msgid,IPC_STAT,buf);

    // �zenetsor adatokat lek�rdezem, benne azt is, h�ny �zenet van m�g
}
	exit (0);
}

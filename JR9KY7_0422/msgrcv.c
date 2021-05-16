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

struct msqid_ds ds, *buf;	// Üzenetsorhoz asszocialt struktura és pointere

int main()
{
	int msgid;		// Üzenetsor azonosító ID
	key_t kulcs;		// Kulcs az üzenetsorhoz
	int tipus, msgflg;	// Típus, flag
	int rtn, meret;		// return es méret

	kulcs = MSGKEY;		// Beállítom a kulcsot
	msgflg = 00666 | IPC_CREAT | MSG_NOERROR;

	msgid = msgget(kulcs, msgflg);
 	if ( msgid == -1) {
                perror("\n Az msgget rendszerhívás sikertelen!");
                exit(-1);
        }
	printf("\n Az üzenet ID: %d",msgid);

	msgp = &rcvbuf;		// Üzenetfogadó buffer
	buf = &ds;		// Üzenetsor jellemzõ adataihoz
	meret = 20;		// Max hossz
	tipus = 0;		// Minden típust várok
	rtn = msgctl(msgid,IPC_STAT,buf); // Üzenetsor adatokat lekerdezem
	printf("\n Az uzenetek szama: %ld",buf->msg_qnum);

	while (buf->msg_qnum) {		// Van-e uzenet?


    // Veszem a következõ üzenetet:
	rtn = msgrcv(msgid,(struct msgbuf *)msgp, meret, tipus, msgflg);
	printf("\n Visszatérés: %d, A fogadott üzenet:%s\n",rtn, msgp->mtext);
	rtn = msgctl(msgid,IPC_STAT,buf);

    // Üzenetsor adatokat lekérdezem, benne azt is, hány üzenet van még
}
	exit (0);
}

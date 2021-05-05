#include <stdlib.h>                                                                                          
#include <unistd.h>
#include <stdio.h>
#include <sys/msg.h>
#include <sys/wait.h>


//ez az általunk meghatározott kulcs az üzenetsorhoz
#define MSGKEY 625694L
//message structure
struct message{
    int message_type;
    int a;
    int b;
}rcvbuf, *msgp;

//struktúra az üzenetsorhoz tartozó adatoknak
struct msqid_ds ds, *buf;


int main(int argc, char* argv[]){


//változók
    //fájl olvasáshoz
    FILE * file_pointer;
    char file_name[50];

    //message queue-hoz
    int msqid;
    key_t key;
    int msgflag, msg_type;
    int ret, msgsize;

    //iterátorok
    int i;
    int j;
    int num_of_rows=0;


//fájl megadása
    if(argc>1){
        file_pointer=fopen(argv[1],"w");
    }
    else
    {
        printf("Kérem adja meg a input fájl nevét kiterjesztéssel együtt!\n");
        int scanret=scanf("%s",file_name);
        printf("%d\n",scanret);
        while(scanret==0)
        {
            printf("Kérem adja meg a input fájl nevét kiterjesztéssel együtt!\n");
            scanret=scanf("%s",file_name);
        }
        file_pointer=fopen(file_name,"w");
    }




    //üzenet sorhoz való csatlakozás
    key=MSGKEY;
    msgflag=00666 | IPC_CREAT | MSG_NOERROR;
    msqid=msgget(key,msgflag);
    if (msqid == -1) {
        perror("msgget() nem sikerult");
        exit(-1);
    }


    msgp=&rcvbuf;
    buf=&ds;
    msg_type=0;
    msgsize=3*sizeof(int)+1;

    ret=msgctl(msqid, IPC_STAT,buf);

    if(buf->msg_qnum==0){
        ret = msgctl(msqid, IPC_RMID, NULL);	
        if(ret==0){
            printf("Message queue sikeresen törölve\n");
        }

    fclose(file_pointer);
    return 0;

    }
    printf("Az uzenetek szama az uzenetsorban: %d\n", (int)buf->msg_qnum);


    while (buf->msg_qnum){

        ret=msgrcv(msqid, (struct message *) msgp, msgsize, msg_type, msgflag);
        int data1=msgp->a;
        int data2=msgp->b;
        int lnko=0;

        
        
        if(data1 < data2){
            lnko=data1;
            data1=data2;
            data2=lnko;
        }
        lnko=data2;
        while(data1%lnko != 0 || data2%lnko != 0){
            lnko = lnko-1;
        }
        

        fprintf(file_pointer, "%d %d %d\n",data1, data2, lnko);
        ret = msgctl(msqid, IPC_STAT, buf);
        printf("Az uzenetek szama az uzenetsorban: %d\n", (int)buf->msg_qnum);
        }

        
        

//az üzenetsor törlése ha üres
    if(buf->msg_qnum==0){
        ret = msgctl(msqid, IPC_RMID, NULL);	
        if(ret==0){
            printf("Message queue sikeresen törölve\n");
        }
    }


    fclose(file_pointer);
    return 0;
}

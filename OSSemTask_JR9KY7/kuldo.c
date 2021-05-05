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
}sendbuf, *msgp;

int main(int argc, char* argv[]){

//változók
    //fájl olvasáshoz
    FILE * file_pointer;
    char file_name[50];

    //message queue-hoz
    int msqid;
    key_t key;
    int msgflag;
    int ret, msgsize;

    //iterátorok
    int i;
    int j;
    int num_of_rows=0;

    // filename beolvasása vagy indítási paraméterből való kiolvasása
    if(argc>1){
        file_pointer=fopen(argv[1],"r");
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
        file_pointer=fopen(file_name,"r");
    }
    

    //fájlból való beolvasás
    int fscan_ret=fscanf(file_pointer, "%d",&num_of_rows);
    if(fscan_ret==0)
        printf("nem sikerült a sorok számát beolvasni");
    int datas[num_of_rows][2];

    for(i=0;i<num_of_rows;i++){
        fscan_ret=fscanf(file_pointer, "%d %d",&datas[i][0],&datas[i][1]);
        if(fscan_ret==0)
            printf("nem sikerült a(z) %d. sort számát beolvasni",i+1);
    }

    //message queue létrehozása és jogosultság, kulcs beállítása
    key = MSGKEY;
	msgflag = 00666 | IPC_CREAT; 
	msqid = msgget(key, msgflag);
    if (msqid == -1) {
        perror(": msgget() nem sikerult!");
        exit(-1);
    }
    printf("Az msgid letrejott: %d\n", msqid);

    msgp=&sendbuf;
    msgp->message_type=2;
    msgsize=3*sizeof(int)+1;

    for(i=0; i<num_of_rows; i++){

        msgp->a=datas[i][0];
        msgp->b=datas[i][1];

        ret=msgsnd(msqid, (struct message *) msgp, msgsize, msgflag); 
        printf("Az %d. küldés visszatérése: %d\n",i, ret);  
        printf("Üzenet:\n %d, %d\n", msgp->a, msgp->b  ) ; 
    }
        fclose(file_pointer);
        return 0;
}
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
#include <stdlib.h>
#define SHMKEY 13

int main()
{
    int shmid;
    key_t kulcs;
    int meret = 512;
    int flag;

    struct str {

        int lng;
        char text[512-sizeof(int)];

    } *segment;

    kulcs = SHMKEY;
    flag = 0;

    if((shmid = shmget(kulcs, meret, flag)) < 0)
    {
        perror("\n Sikertelen volt az shmget!\n");
        exit(-1);
    }

    flag = 00666 | SHM_RND;
    segment = (struct str *)shmat(shmid, NULL, flag);

    if(segment == (void *) - 1)
    {
        perror("\n Sikertelen csatlakozás!");
        exit(-1);
    }

    if(strlen(segment->text) > 0)
    {
        printf("\n A régi szöveg : %s", segment->text);
    }

    printf("\n Adja meg az új szöveget : ");
    scanf("%s", segment->text);
    printf("\n\n Az új szöveg : %s \n", segment->text);

    shmdt(segment);
    exit(0);
}

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
#define SHMKEY 13


struct str {

    int lng;
    char text[512-sizeof(int)];

} *segment;



int main()
{
    int shmid, flag, rtn, choose;
    int size = 512;
    key_t key;

    key = SHMKEY;
    flag = 0;

    if((shmid = shmget(key, size, flag)) < 0)
    {
        flag = 00666 | IPC_CREAT;
        if((shmid = shmget(key, size, flag)) < 0)
        {
            perror("\nSikertelen shmget!");
            return -1;
        }
    }

    printf("\nAz azonos�t� : %d\n", shmid);

    flag = 00666 | SHM_RND;
    segment = (struct str *)shmat(shmid, NULL, flag);

    if(segment == (void *) - 1)
    {
        perror("\n Sikertelen csatlakozas");
        return -1;
    }

    if(strlen(segment->text) > 0)
    {
        printf("\nR�gi szoveg : %s", segment->text);
    }

    printf("\n�j sz�veget : ");
    scanf("%s", segment->text);
    printf("\nAz �j sz�veg: %s \n", segment->text);

    shmdt(segment);
    struct shmid_ds shmid_ds, *buf;
    buf = &shmid_ds;
    flag = 0;

    do {
        printf("V�lasszon a men�b�l\n");
        printf("0. st�tusz lek�r�se\n");
        printf("1. szegmens t�rl�se\n");
        scanf("%d", &choose);

    }while(choose != 0 && choose != 1);

    switch(choose){
    case 0:
        rtn = shmctl(shmid, IPC_STAT, buf);
        printf("\nM�ret: %ld", buf->shm_segsz);
        printf("\nPID: %d\n", buf->shm_lpid);
        break;

    case 1:
        rtn = shmctl(shmid, IPC_RMID, NULL);
        printf("\nSzegmens megsz�ntetve!\n");
        break;
    }

    return 0;
}

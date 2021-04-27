#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>


int main(){

    int fd;
    pid_t gyerek;

    if((mkfifo("JR9KY7", S_IRUSR | S_IWUSR)) < 0)
	{
        printf("RENDSZER: Nem sikerult a FIFO letrehozasa!\n");
        exit(1);
	}

    if((gyerek = fork()) < 0){
        printf("RENDSZER: Nem sikerult a gyerek fork processz letrehozasa!\n");
        exit(1);
    }
	else
	{
		printf("RENDSZER: A gyerek processz elindult!\n\n");
	}

    //A gyerek processze
    if(!gyerek){
        char *uzenet = "Fekete Mate";


        if((fd = open("JR9KY7", O_WRONLY)) < 0){
            printf("GYEREK: Nem sikerult a FIFO megnyitasa!\n");
            exit(1);


        } else {

            printf("GYEREK: FIFO megnyitva csak irasra, iras folyamatban...\n");
            write(fd, uzenet, strlen(uzenet));

        }
        printf("RENDSZER: A gyerek processz sikeresen befejezete az irast,\na gyerek processz kilep.\n\n");
		printf("RENDSZER: Szulo processz inditasa\n");
    }

    //A szulo processze
    if(gyerek){
        char buf[256];
        if((fd = open("JR9KY7", O_RDONLY)) <0 ){

            printf("SZULO: Nem sikerult a FIFO megnyitasa!\n");
            exit(1);

        } else {

            printf("SZULO: FIFO megnyitva csak olvasasra, olvasas folyamatban...\n");
            read(fd, buf, sizeof(buf));
            printf("SZULO: Kiolvasott adat: %s.\n\n", buf);

            printf("RENDSZER: A szulo processz sikeresen befejezete az olvasast.\n");

        }
        if((unlink("JR9KY7")) < 0 || (close(fd)) < 0){

            printf("RENDSZER: Nem sikerult a FIFO torlese!");

        } else {

            printf("RENDSZER: FIFO sikeresen torolve, kilepes.\n");
        }
	}


    return 0;

}

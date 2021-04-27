#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{

int i = 0;


    pid_t pid=fork();
    if (pid==0) {
        printf("---Gyermek processz---\n");
        do
        {
            printf("\n Neve: Fekete Mate\nNeptun kód: JR9KY7\n\n");
            i++;


        }while (i<5);

        exit(127);
    }
    else {
        waitpid(pid,0,0);



        printf("---Szülõ processz---\n\nA gyermek processz befejezte a futását!\n");
    }
    return 0;
}

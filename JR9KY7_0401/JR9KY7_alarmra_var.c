#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

void ures();

int main(){

    unsigned sec = 5;
    signal(SIGALRM, ures);
    alarm(sec);


    printf("%d varok.\n",1);
    pause();

    printf("Megerkezett az alarm.\n");

 return 0;
}


void ures(){
;
}

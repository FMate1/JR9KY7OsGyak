#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>


void terminal(int sig);

int main(void)
{
    if (signal(SIGKILL, terminal) == SIG_ERR)
    {
        printf("A(z) \"SIGKILL\" jelre nem sikerult handlert allitani!\n");
        return 0;
    }

    while(-1)
    {
        printf("Varakozok...\n");
        sleep(3);
    }

    return 0;
}

void terminal(int sig){

    signal(sig, SIG_IGN);
    printf("Jel: %d\n", sig);
}

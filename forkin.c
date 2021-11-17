#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

int main() {
    //setting up rand
    srand( time(NULL));
    int x;


    printf("Parent: Hey what's up guys\n");
    int id = fork(); 
    int pid1;
    if (id == 0)
        pid1 = getpid(); // this allows for rand to not output the same number for the two child processes
    if (id != 0) {
        id = fork(); // creates 2 child processes
    }

    if (id == 0) {
        int num;
        if (getpid() == pid1)
            num = 1;
        else
            num = 2;
        printf("Child %d: My pid is %d\n", num, getpid());
        x = rand();
        if (num == 1) // calls rand again to get a different number for the first child process
            x = rand();
        printf("Child %d: Sleeping for %d seconds\n", num, 2 + x % 4);
        sleep(2 + x % 4);
        printf("Child %d: Awake\n", num);
        return 2 + x % 4; // child processes return the time they slept
    }

    if (id != 0) {
        int status;
        int childpid = wait(&status);
        printf("Parent: pid of exited is %d, asleep for %d seconds\n", childpid, WEXITSTATUS(status)); //WEXITSTATUS gets the return value, the time slept

        printf("Parent: Done!\n");
        return 0;
    }


}
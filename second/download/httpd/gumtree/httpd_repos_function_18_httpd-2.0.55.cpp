void accept_mutex_on()
{
    switch(ussetlock(uslock)) {
        case 1:
            /* got lock */
            break;
        case 0:
            fprintf(stderr, "didn't get lock\n");
            exit(-1);
        case -1:
            perror("ussetlock");
            exit(-1);
    }
}
    FILE *fp;

    if (fork() != 0) exit(0); /* parent exits */
    printf("New pid: %d\n", getpid());
    setsid(); /* create a new session */

    /* Every output goes to /dev/null. If Redis is daemonized but

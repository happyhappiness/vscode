static void ssl_rand_seed(void)
{
    int nDone = 0;
    int n, l;
    time_t t;
    pid_t pid;
    unsigned char stackdata[256];

    /*
     * seed in the current time (usually just 4 bytes)
     */
    t = time(NULL);
    l = sizeof(time_t);
    RAND_seed((unsigned char *)&t, l);
    nDone += l;

    /*
     * seed in the current process id (usually just 4 bytes)
     */
    pid = getpid();
    l = sizeof(pid_t);
    RAND_seed((unsigned char *)&pid, l);
    nDone += l;

    /*
     * seed in some current state of the run-time stack (128 bytes)
     */
    n = ssl_rand_choosenum(0, sizeof(stackdata)-128-1);
    RAND_seed(stackdata+n, 128);
    nDone += 128;
}
void main (int argc, char **argv)
{
    int num_iter;
    int num_child;
    int i;
    struct timeval first;
    struct timeval last;
    long ms;
    int pid;
    unsigned long *shared_counter;

    if (argc != 3) {
        fprintf (stderr, "Usage: time-sem num-child num iter\n");
        exit (1);
    }

    num_child = atoi (argv[1]);
    num_iter = atoi (argv[2]);

    /* allocate shared memory for the shared_counter */
    shared_counter = get_shared_mem(sizeof(*shared_counter));

    /* initialize counter to 0 */
    *shared_counter = 0;

    accept_mutex_init ();

    /* parent grabs mutex until done spawning children */
    accept_mutex_on ();

    for (i = 0; i < num_child; ++i) {
        pid = fork();
        if (pid == 0) {
            /* child, do our thing */
            accept_mutex_child_init();
            for (i = 0; i < num_iter; ++i) {
                unsigned long tmp;

                accept_mutex_on ();
                tmp = *shared_counter;
                YIELD;
                *shared_counter = tmp + 1;
                accept_mutex_off ();
            }
            exit (0);
        } else if (pid == -1) {
            perror ("fork");
            exit (1);
        }
    }

    /* a quick test to see that nothing is screwed up */
    if (*shared_counter != 0) {
        puts ("WTF! shared_counter != 0 before the children have been started!");
        exit (1);
    }

    gettimeofday (&first, NULL);
    /* launch children into action */
    accept_mutex_off ();
    for (i = 0; i < num_child; ++i) {
        if (wait(NULL) == -1) {
            perror ("wait");
        }
    }
    gettimeofday (&last, NULL);

    if (*shared_counter != num_child * num_iter) {
        printf ("WTF! shared_counter != num_child * num_iter!\n"
                "shared_counter = %lu\nnum_child = %d\nnum_iter=%d\n",
                *shared_counter,
                num_child, num_iter);
    }

    last.tv_sec -= first.tv_sec;
    ms = last.tv_usec - first.tv_usec;
    if (ms < 0) {
        --last.tv_sec;
        ms += 1000000;
    }
    last.tv_usec = ms;
    printf ("%8lu.%06lu\n", last.tv_sec, last.tv_usec);

    accept_mutex_cleanup();

    exit(0);
}
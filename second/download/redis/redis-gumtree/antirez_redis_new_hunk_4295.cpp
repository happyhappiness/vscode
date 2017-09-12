    int j;
    time_t now = time(NULL);

    waitEmptyIOJobsQueue(); /* Otherwise other threads may fseek() the swap */
    snprintf(tmpfile,256,"temp-%d.rdb", (int) getpid());
    fp = fopen(tmpfile,"w");
    if (!fp) {

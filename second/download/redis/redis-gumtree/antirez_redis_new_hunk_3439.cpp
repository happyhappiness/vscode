    int j;
    time_t now = time(NULL);

    /* FIXME: implement .rdb save for disk store properly */
    redisAssert(server.ds_enabled == 0);

    snprintf(tmpfile,256,"temp-%d.rdb", (int) getpid());
    fp = fopen(tmpfile,"w");

    long long now = mstime();
    FILE *fp;
    rio rdb;

    snprintf(tmpfile,256,"temp-%d.rdb", (int) getpid());
    fp = fopen(tmpfile,"w");

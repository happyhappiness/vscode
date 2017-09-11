    long long now = mstime();
    FILE *fp;
    rio rdb;
    uint64_t cksum;

    snprintf(tmpfile,256,"temp-%d.rdb", (int) getpid());
    fp = fopen(tmpfile,"w");

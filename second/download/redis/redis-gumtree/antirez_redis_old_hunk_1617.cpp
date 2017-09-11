    char tmpfile[256];
    FILE *fp;
    rio rdb;
    int error;

    snprintf(tmpfile,256,"temp-%d.rdb", (int) getpid());
    fp = fopen(tmpfile,"w");

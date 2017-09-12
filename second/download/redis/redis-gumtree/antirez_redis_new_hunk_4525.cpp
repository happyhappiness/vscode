    FILE *fp;
    char tmpfile[256];
    int j;
    time_t now = time(NULL);

    snprintf(tmpfile,256,"temp-%d.%ld.rdb",(int)time(NULL),(long int)random());
    fp = fopen(tmpfile,"w");

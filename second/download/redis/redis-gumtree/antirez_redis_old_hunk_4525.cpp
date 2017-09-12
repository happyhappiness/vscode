    FILE *fp;
    char tmpfile[256];
    int j;

    snprintf(tmpfile,256,"temp-%d.%ld.rdb",(int)time(NULL),(long int)random());
    fp = fopen(tmpfile,"w");

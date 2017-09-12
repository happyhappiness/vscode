    }
}

int dsRdbSave(char *filename) {
    char tmpfile[256];
    int j, i;
    time_t now = time(NULL);

    snprintf(tmpfile,256,"temp-%d.rdb", (int) getpid());
    fp = fopen(tmpfile,"w");
    if (!fp) {

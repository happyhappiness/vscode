    return REDIS_OK; /* unreached */
}

static void rdbRemoveTempFile(pid_t childpid) {
    char tmpfile[256];

    snprintf(tmpfile,256,"temp-%d.rdb", (int) childpid);
    unlink(tmpfile);
}

static int rdbLoadType(FILE *fp) {
    unsigned char type;
    if (fread(&type,1,1,fp) == 0) return -1;

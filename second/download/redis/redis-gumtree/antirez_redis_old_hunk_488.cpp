/* Save the DB on disk. Return C_ERR on error, C_OK on success. */
int rdbSave(char *filename) {
    char tmpfile[256];
    FILE *fp;
    rio rdb;
    int error = 0;

    snprintf(tmpfile,256,"temp-%d.rdb", (int) getpid());
    fp = fopen(tmpfile,"w");
    if (!fp) {
        serverLog(LL_WARNING, "Failed opening .rdb for saving: %s",
            strerror(errno));
        return C_ERR;
    }

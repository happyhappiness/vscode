    snprintf(tmpfile,256,"temp-%d.rdb", (int) getpid());
    fp = fopen(tmpfile,"w");
    if (!fp) {
        serverLog(LL_WARNING, "Failed opening .rdb for saving: %s",
            strerror(errno));
        return C_ERR;
    }

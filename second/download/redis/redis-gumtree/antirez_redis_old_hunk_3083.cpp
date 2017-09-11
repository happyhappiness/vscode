    int j;
    time_t now = time(NULL);

    if (server.ds_enabled) {
        cacheForcePointInTime();
        return dsRdbSave(filename);
    }

    snprintf(tmpfile,256,"temp-%d.rdb", (int) getpid());
    fp = fopen(tmpfile,"w");
    if (!fp) {

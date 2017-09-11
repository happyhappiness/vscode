void loadDataFromDisk(void) {
    long long start = ustime();
    if (server.aof_state == REDIS_AOF_ON) {
        if (loadAppendOnlyFile(server.aof_filename) == REDIS_OK)
            serverLog(REDIS_NOTICE,"DB loaded from append only file: %.3f seconds",(float)(ustime()-start)/1000000);
    } else {
        if (rdbLoad(server.rdb_filename) == REDIS_OK) {
            serverLog(REDIS_NOTICE,"DB loaded from disk: %.3f seconds",
                (float)(ustime()-start)/1000000);
        } else if (errno != ENOENT) {

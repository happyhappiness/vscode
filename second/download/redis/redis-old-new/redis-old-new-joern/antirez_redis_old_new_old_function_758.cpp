void clusterSaveConfigOrDie(int do_fsync) {
    if (clusterSaveConfig(do_fsync) == -1) {
        serverLog(REDIS_WARNING,"Fatal: can't update cluster config file.");
        exit(1);
    }
}
    return -1;
}

void clusterSaveConfigOrDie(int do_fsync) {
    if (clusterSaveConfig(do_fsync) == -1) {
        redisLog(REDIS_WARNING,"Fatal: can't update cluster config file.");
        exit(1);
    }

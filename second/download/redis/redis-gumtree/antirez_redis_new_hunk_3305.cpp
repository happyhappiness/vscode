    return -1;
}

void clusterSaveConfigOrDie(void) {
    if (clusterSaveConfig() == -1) {
        redisLog(REDIS_WARNING,"Fatal: can't update cluster config file.");
        exit(1);
    }
}

void clusterInit(void) {
    int saveconf = 0;


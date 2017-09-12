
void *dsRdbSave_thread(void *arg) {
    char tmpfile[256], *filename = (char*)arg;
    struct dirent *dp, de;
    int j, i, last_dbid = -1;
    FILE *fp;

    /* Change state to ACTIVE, to signal there is a saving thead working. */
    redisLog(REDIS_NOTICE,"Diskstore BGSAVE thread started");
    dsRdbSaveSetState(REDIS_BGSAVE_THREAD_ACTIVE);

    snprintf(tmpfile,256,"temp-%d.rdb", (int) getpid());
    fp = fopen(tmpfile,"w");

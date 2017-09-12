    }
}

void *dsRdbSave_thread(void *arg) {
    char tmpfile[256], *filename = (char*)arg;
    int j, i;
    time_t now = time(NULL);

    /* Change state to ACTIVE, to signal there is a saving thead working. */
    pthread_mutex_lock(&server.bgsavethread_mutex);
    server.bgsavethread_state = REDIS_BGSAVE_THREAD_ACTIVE;
    pthread_mutex_unlock(&server.bgsavethread_mutex);

    snprintf(tmpfile,256,"temp-%d.rdb", (int) getpid());
    fp = fopen(tmpfile,"w");
    if (!fp) {

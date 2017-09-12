int dsRdbSave(char *filename) {
    pthread_t thread;

    if (pthread_create(&thread,NULL,dsRdbSave_thread,zstrdup(filename)) != 0) {
        redisLog(REDIS_WARNING,"Can't create diskstore BGSAVE thread: %s",
            strerror(errno));
        return REDIS_ERR;
    } else {
        server.bgsavethread = thread;
        return REDIS_OK;
    }
}
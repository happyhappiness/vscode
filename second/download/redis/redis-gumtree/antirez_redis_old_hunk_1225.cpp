     * processes. */
    int fd = open(filename,O_WRONLY|O_CREAT,0644);
    if (fd == -1) {
        redisLog(REDIS_WARNING,
            "Can't open %s in order to acquire a lock: %s",
            filename, strerror(errno));
        return REDIS_ERR;
    }

    if (flock(fd,LOCK_EX|LOCK_NB) == -1) {
        if (errno == EWOULDBLOCK) {
            redisLog(REDIS_WARNING,
                 "Sorry, the cluster configuration file %s is already used "
                 "by a different Redis Cluster node. Please make sure that "
                 "different nodes use different cluster configuration "
                 "files.", filename);
        } else {
            redisLog(REDIS_WARNING,
                "Impossible to lock %s: %s", filename, strerror(errno));
        }
        close(fd);

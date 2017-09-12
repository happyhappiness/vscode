void adjustOpenFilesLimit(void) {
    rlim_t maxfiles = server.maxclients+32;
    struct rlimit limit;

    if (maxfiles < 1024) maxfiles = 1024;
    if (getrlimit(RLIMIT_NOFILE,&limit) == -1) {
        redisLog(REDIS_WARNING,"Unable to obtain the current NOFILE limit (%s), assuming 1024 and setting the max clients configuration accordingly.",
            strerror(errno));
        server.maxclients = 1024-32;
    } else {
        rlim_t oldlimit = limit.rlim_cur;

        /* Set the max number of files if the current limit is not enough
         * for our needs. */
        if (oldlimit < maxfiles) {
            limit.rlim_cur = maxfiles;
            limit.rlim_max = maxfiles;
            if (setrlimit(RLIMIT_NOFILE,&limit) == -1) {
                server.maxclients = oldlimit-32;
                redisLog(REDIS_WARNING,"Unable to set the max number of files limit to %d (%s), setting the max clients configuration to %d.",
                    (int) maxfiles, strerror(errno), (int) server.maxclients);
            } else {
                redisLog(REDIS_NOTICE,"Max number of open files set to %d",
                    (int) maxfiles);
            }
        }
    }
}
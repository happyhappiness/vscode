    int save = flags & REDIS_SHUTDOWN_SAVE;
    int nosave = flags & REDIS_SHUTDOWN_NOSAVE;

    redisLog(REDIS_WARNING,"User requested shutdown...");
    /* Kill the saving child if there is a background saving in progress.
       We want to avoid race conditions, for instance our saving child may
       overwrite the synchronous saving did by SHUTDOWN. */
    if (server.rdb_child_pid != -1) {
        redisLog(REDIS_WARNING,"There is a child saving an .rdb. Killing it!");
        kill(server.rdb_child_pid,SIGUSR1);
        rdbRemoveTempFile(server.rdb_child_pid);
    }

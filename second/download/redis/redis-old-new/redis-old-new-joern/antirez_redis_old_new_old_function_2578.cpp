void flushAppendOnlyFile(int force) {
    ssize_t nwritten;
    int sync_in_progress = 0;

    if (sdslen(server.aof_buf) == 0) return;

    if (server.aof_fsync == AOF_FSYNC_EVERYSEC)
        sync_in_progress = bioPendingJobsOfType(REDIS_BIO_AOF_FSYNC) != 0;

    if (server.aof_fsync == AOF_FSYNC_EVERYSEC && !force) {
        /* With this append fsync policy we do background fsyncing.
         * If the fsync is still in progress we can try to delay
         * the write for a couple of seconds. */
        if (sync_in_progress) {
            if (server.aof_flush_postponed_start == 0) {
                /* No previous write postponinig, remember that we are
                 * postponing the flush and return. */
                server.aof_flush_postponed_start = server.unixtime;
                return;
            } else if (server.unixtime - server.aof_flush_postponed_start < 2) {
                /* We were already waiting for fsync to finish, but for less
                 * than two seconds this is still ok. Postpone again. */
                return;
            }
            /* Otherwise fall trough, and go write since we can't wait
             * over two seconds. */
            redisLog(REDIS_NOTICE,"Asynchronous AOF fsync is taking too long (disk is busy?). Writing the AOF buffer without waiting for fsync to complete, this may slow down Redis.");
        }
    }
    /* If you are following this code path, then we are going to write so
     * set reset the postponed flush sentinel to zero. */
    server.aof_flush_postponed_start = 0;

    /* We want to perform a single write. This should be guaranteed atomic
     * at least if the filesystem we are writing is a real physical one.
     * While this will save us against the server being killed I don't think
     * there is much to do about the whole server stopping for power problems
     * or alike */
    nwritten = write(server.aof_fd,server.aof_buf,sdslen(server.aof_buf));
    if (nwritten != (signed)sdslen(server.aof_buf)) {
        /* Ooops, we are in troubles. The best thing to do for now is
         * aborting instead of giving the illusion that everything is
         * working as expected. */
        if (nwritten == -1) {
            redisLog(REDIS_WARNING,"Exiting on error writing to the append-only file: %s",strerror(errno));
        } else {
            redisLog(REDIS_WARNING,"Exiting on short write while writing to the append-only file: %s",strerror(errno));
        }
        exit(1);
    }
    server.aof_current_size += nwritten;

    /* Re-use AOF buffer when it is small enough. The maximum comes from the
     * arena size of 4k minus some overhead (but is otherwise arbitrary). */
    if ((sdslen(server.aof_buf)+sdsavail(server.aof_buf)) < 4000) {
        sdsclear(server.aof_buf);
    } else {
        sdsfree(server.aof_buf);
        server.aof_buf = sdsempty();
    }

    /* Don't fsync if no-appendfsync-on-rewrite is set to yes and there are
     * children doing I/O in the background. */
    if (server.aof_no_fsync_on_rewrite &&
        (server.aof_child_pid != -1 || server.rdb_child_pid != -1))
            return;

    /* Perform the fsync if needed. */
    if (server.aof_fsync == AOF_FSYNC_ALWAYS) {
        /* aof_fsync is defined as fdatasync() for Linux in order to avoid
         * flushing metadata. */
        aof_fsync(server.aof_fd); /* Let's try to get this data on the disk */
        server.aof_last_fsync = server.unixtime;
    } else if ((server.aof_fsync == AOF_FSYNC_EVERYSEC &&
                server.unixtime > server.aof_last_fsync)) {
        if (!sync_in_progress) aof_background_fsync(server.aof_fd);
        server.aof_last_fsync = server.unixtime;
    }
}
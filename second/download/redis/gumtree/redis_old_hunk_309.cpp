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
            redisLog(REDIS_WARNING,"Exiting on short write while writing to "
                                   "the append-only file: %s (nwritten=%ld, "
                                   "expected=%ld)",
                                   strerror(errno),
                                   (long)nwritten,
                                   (long)sdslen(server.aof_buf));

            if (ftruncate(server.aof_fd, server.aof_current_size) == -1) {
                redisLog(REDIS_WARNING, "Could not remove short write "
                         "from the append-only file.  Redis may refuse "
                         "to load the AOF the next time it starts.  "
                         "ftruncate: %s", strerror(errno));
            }
        }
        exit(1);
    }
    server.aof_current_size += nwritten;

    /* Re-use AOF buffer when it is small enough. The maximum comes from the
     * arena size of 4k minus some overhead (but is otherwise arbitrary). */
    if ((sdslen(server.aof_buf)+sdsavail(server.aof_buf)) < 4000) {

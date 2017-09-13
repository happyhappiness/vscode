static void flushAppendOnlyFile(void) {
    time_t now;
    ssize_t nwritten;

    if (sdslen(server.aofbuf) == 0) return;

    /* We want to perform a single write. This should be guaranteed atomic
     * at least if the filesystem we are writing is a real physical one.
     * While this will save us against the server being killed I don't think
     * there is much to do about the whole server stopping for power problems
     * or alike */
     nwritten = write(server.appendfd,server.aofbuf,sdslen(server.aofbuf));
     if (nwritten != (signed)sdslen(server.aofbuf)) {
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
    sdsfree(server.aofbuf);
    server.aofbuf = sdsempty();

    /* Fsync if needed */
    now = time(NULL);
    if (server.appendfsync == APPENDFSYNC_ALWAYS ||
        (server.appendfsync == APPENDFSYNC_EVERYSEC &&
         now-server.lastfsync > 1))
    {
        /* aof_fsync is defined as fdatasync() for Linux in order to avoid
         * flushing metadata. */
        aof_fsync(server.appendfd); /* Let's try to get this data on the disk */
        server.lastfsync = now;
    }
}
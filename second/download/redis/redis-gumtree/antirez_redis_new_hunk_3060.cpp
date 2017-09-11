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

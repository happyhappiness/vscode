    /* Use RENAME to make sure the DB file is changed atomically only
     * if the generate DB file is ok. */
    if (rename(tmpfile,filename) == -1) {
        redisLog(REDIS_WARNING,"Error moving temp DB file on the final destination: %s (diskstore)", strerror(errno));
        unlink(tmpfile);
        dsRdbSaveSetState(REDIS_BGSAVE_THREAD_DONE_ERR);
        return NULL;

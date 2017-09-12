void *dsRdbSave_thread(void *arg) {
    char tmpfile[256], *filename = (char*)arg;
    int j, i;
    time_t now = time(NULL);
    FILE *fp;

    /* Change state to ACTIVE, to signal there is a saving thead working. */
    pthread_mutex_lock(&server.bgsavethread_mutex);
    server.bgsavethread_state = REDIS_BGSAVE_THREAD_ACTIVE;
    pthread_mutex_unlock(&server.bgsavethread_mutex);

    snprintf(tmpfile,256,"temp-%d.rdb", (int) getpid());
    fp = fopen(tmpfile,"w");
    if (!fp) {
        redisLog(REDIS_WARNING, "Failed opening .rdb for saving: %s",
            strerror(errno));
        dsRdbSaveSetState(REDIS_BGSAVE_THREAD_DONE_ERR);
        return NULL;
    }
    if (fwrite("REDIS0001",9,1,fp) == 0) goto werr;

    sleep(5);

#if 0
    /* Scan all diskstore dirs looking for keys */
    for (j = 0; j < 256; j++) {
        for (i = 0; i < 256; i++) {
            snprintf(buf,1024,"%s/%02x/%02x",server.ds_path,j,i);

            /* Write the SELECT DB opcode */
            if (rdbSaveType(fp,REDIS_SELECTDB) == -1) goto werr;
            if (rdbSaveLen(fp,j) == -1) goto werr;
        }
    }
#endif

    /* Make sure data will not remain on the OS's output buffers */
    fflush(fp);
    fsync(fileno(fp));
    fclose(fp);
    zfree(filename);

    /* Use RENAME to make sure the DB file is changed atomically only
     * if the generate DB file is ok. */
    if (rename(tmpfile,filename) == -1) {
        redisLog(REDIS_WARNING,"Error moving temp DB file on the final destination: %s", strerror(errno));
        unlink(tmpfile);
        dsRdbSaveSetState(REDIS_BGSAVE_THREAD_DONE_ERR);
        return NULL;
    }
    redisLog(REDIS_NOTICE,"DB saved on disk");
    dsRdbSaveSetState(REDIS_BGSAVE_THREAD_DONE_OK);
    return NULL;

werr:
    zfree(filename);
    fclose(fp);
    unlink(tmpfile);
    dsRdbSaveSetState(REDIS_BGSAVE_THREAD_DONE_ERR);
    redisLog(REDIS_WARNING,"Write error saving DB on disk: %s", strerror(errno));
    return NULL;
}
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

int dsRdbSave(char *filename) {

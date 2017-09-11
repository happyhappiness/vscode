    /* Use RENAME to make sure the DB file is changed atomically only
     * if the generate DB file is ok. */
    if (rename(tmpfile,filename) == -1) {
        serverLog(REDIS_WARNING,"Error moving temp append only file on the final destination: %s", strerror(errno));
        unlink(tmpfile);
        return C_ERR;
    }
    serverLog(REDIS_NOTICE,"SYNC append only file rewrite performed");
    return C_OK;

werr:
    serverLog(REDIS_WARNING,"Write error writing append only file on disk: %s", strerror(errno));
    fclose(fp);
    unlink(tmpfile);
    if (di) dictReleaseIterator(di);

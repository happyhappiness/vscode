static int rewriteAppendOnlyFile(char *filename) {
    dictIterator *di = NULL;
    dictEntry *de;
    FILE *fp;
    char tmpfile[256];
    int j;
    time_t now = time(NULL);

    /* Note that we have to use a different temp name here compared to the
     * one used by rewriteAppendOnlyFileBackground() function. */
    snprintf(tmpfile,256,"temp-rewriteaof-%d.aof", (int) getpid());
    fp = fopen(tmpfile,"w");
    if (!fp) {
        redisLog(REDIS_WARNING, "Failed rewriting the append only file: %s", strerror(errno));
        return REDIS_ERR;
    }
    for (j = 0; j < server.dbnum; j++) {
        char selectcmd[] = "*2\r\n$6\r\nSELECT\r\n";
        redisDb *db = server.db+j;
        dict *d = db->dict;
        if (dictSize(d) == 0) continue;
        di = dictGetIterator(d);
        if (!di) {
            fclose(fp);
            return REDIS_ERR;
        }

        /* SELECT the new DB */
        if (fwrite(selectcmd,sizeof(selectcmd)-1,1,fp) == 0) goto werr;
        if (fwriteBulkLong(fp,j) == 0) goto werr;

        /* Iterate this DB writing every entry */
        while((de = dictNext(di)) != NULL) {
            robj *key = dictGetEntryKey(de);
            robj *o = dictGetEntryVal(de);
            time_t expiretime = getExpire(db,key);

            /* Save the key and associated value */
            if (o->type == REDIS_STRING) {
                /* Emit a SET command */
                char cmd[]="*3\r\n$3\r\nSET\r\n";
                if (fwrite(cmd,sizeof(cmd)-1,1,fp) == 0) goto werr;
                /* Key and value */
                if (fwriteBulk(fp,key) == 0) goto werr;
                if (fwriteBulk(fp,o) == 0) goto werr;
            } else if (o->type == REDIS_LIST) {
                /* Emit the RPUSHes needed to rebuild the list */
                list *list = o->ptr;
                listNode *ln;

                listRewind(list);
                while((ln = listYield(list))) {
                    char cmd[]="*3\r\n$5\r\nRPUSH\r\n";
                    robj *eleobj = listNodeValue(ln);

                    if (fwrite(cmd,sizeof(cmd)-1,1,fp) == 0) goto werr;
                    if (fwriteBulk(fp,key) == 0) goto werr;
                    if (fwriteBulk(fp,eleobj) == 0) goto werr;
                }
            } else if (o->type == REDIS_SET) {
                /* Emit the SADDs needed to rebuild the set */
                dict *set = o->ptr;
                dictIterator *di = dictGetIterator(set);
                dictEntry *de;

                while((de = dictNext(di)) != NULL) {
                    char cmd[]="*3\r\n$4\r\nSADD\r\n";
                    robj *eleobj = dictGetEntryKey(de);

                    if (fwrite(cmd,sizeof(cmd)-1,1,fp) == 0) goto werr;
                    if (fwriteBulk(fp,key) == 0) goto werr;
                    if (fwriteBulk(fp,eleobj) == 0) goto werr;
                }
                dictReleaseIterator(di);
            } else if (o->type == REDIS_ZSET) {
                /* Emit the ZADDs needed to rebuild the sorted set */
                zset *zs = o->ptr;
                dictIterator *di = dictGetIterator(zs->dict);
                dictEntry *de;

                while((de = dictNext(di)) != NULL) {
                    char cmd[]="*4\r\n$4\r\nZADD\r\n";
                    robj *eleobj = dictGetEntryKey(de);
                    double *score = dictGetEntryVal(de);

                    if (fwrite(cmd,sizeof(cmd)-1,1,fp) == 0) goto werr;
                    if (fwriteBulk(fp,key) == 0) goto werr;
                    if (fwriteBulkDouble(fp,*score) == 0) goto werr;
                    if (fwriteBulk(fp,eleobj) == 0) goto werr;
                }
                dictReleaseIterator(di);
            } else {
                redisAssert(0 != 0);
            }
            /* Save the expire time */
            if (expiretime != -1) {
                char cmd[]="*3\r\n$6\r\nEXPIRE\r\n";
                /* If this key is already expired skip it */
                if (expiretime < now) continue;
                if (fwrite(cmd,sizeof(cmd)-1,1,fp) == 0) goto werr;
                if (fwriteBulk(fp,key) == 0) goto werr;
                if (fwriteBulkLong(fp,expiretime) == 0) goto werr;
            }
        }
        dictReleaseIterator(di);
    }

    /* Make sure data will not remain on the OS's output buffers */
    fflush(fp);
    fsync(fileno(fp));
    fclose(fp);
    
    /* Use RENAME to make sure the DB file is changed atomically only
     * if the generate DB file is ok. */
    if (rename(tmpfile,filename) == -1) {
        redisLog(REDIS_WARNING,"Error moving temp append only file on the final destination: %s", strerror(errno));
        unlink(tmpfile);
        return REDIS_ERR;
    }
    redisLog(REDIS_NOTICE,"SYNC append only file rewrite performed");
    return REDIS_OK;

werr:
    fclose(fp);
    unlink(tmpfile);
    redisLog(REDIS_WARNING,"Write error writing append only fileon disk: %s", strerror(errno));
    if (di) dictReleaseIterator(di);
    return REDIS_ERR;
}
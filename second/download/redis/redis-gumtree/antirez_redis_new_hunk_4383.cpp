    exit(1);
}

/* Write an object into a file in the bulk format $<count>\r\n<payload>\r\n */
static int fwriteBulk(FILE *fp, robj *obj) {
    char buf[128];
    obj = getDecodedObject(obj);
    snprintf(buf,sizeof(buf),"$%ld\r\n",(long)sdslen(obj->ptr));
    if (fwrite(buf,strlen(buf),1,fp) == 0) goto err;
    if (fwrite(obj->ptr,sdslen(obj->ptr),1,fp) == 0) goto err;
    if (fwrite("\r\n",2,1,fp) == 0) goto err;
    decrRefCount(obj);
    return 1;
err:
    decrRefCount(obj);
    return 0;
}

/* Write a double value in bulk format $<count>\r\n<payload>\r\n */
static int fwriteBulkDouble(FILE *fp, double d) {
    char buf[128], dbuf[128];

    snprintf(dbuf,sizeof(dbuf),"%.17g\r\n",d);
    snprintf(buf,sizeof(buf),"$%lu\r\n",(unsigned long)strlen(dbuf)-2);
    if (fwrite(buf,strlen(buf),1,fp) == 0) return 0;
    if (fwrite(dbuf,strlen(dbuf),1,fp) == 0) return 0;
    return 1;
}

/* Write a long value in bulk format $<count>\r\n<payload>\r\n */
static int fwriteBulkLong(FILE *fp, long l) {
    char buf[128], lbuf[128];

    snprintf(lbuf,sizeof(lbuf),"%ld\r\n",l);
    snprintf(buf,sizeof(buf),"$%lu\r\n",(unsigned long)strlen(lbuf)-2);
    if (fwrite(buf,strlen(buf),1,fp) == 0) return 0;
    if (fwrite(lbuf,strlen(lbuf),1,fp) == 0) return 0;
    return 1;
}

/* Write a sequence of commands able to fully rebuild the dataset into
 * "filename". Used both by REWRITEAOF and BGREWRITEAOF. */
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
        if (fwriteBulkLong(fp,j+1) == 0) goto werr;

        /* Iterate this DB writing every entry */
        while((de = dictNext(di)) != NULL) {
            robj *key = dictGetEntryKey(de);
            robj *o = dictGetEntryVal(de);
            time_t expiretime = getExpire(db,key);

            /* Save the key and associated value */
            if (rdbSaveStringObject(fp,key) == -1) goto werr;
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
                assert(0 != 0);
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

/* This is how rewriting of the append only file in background works:
 *
 * 1) The user calls BGREWRITEAOF
 * 2) Redis calls this function, that forks():
 *    2a) the child rewrite the append only file in a temp file.
 *    2b) the parent accumulates differences in server.bgrewritebuf.
 * 3) When the child finished '2a' exists.
 * 4) The parent will trap the exit code, if it's OK, will append the
 *    data accumulated into server.bgrewritebuf into the temp file, and
 *    finally will rename(2) the temp file in the actual file name.
 *    The the new file is reopened as the new append only file. Profit!
 */
static int rewriteAppendOnlyFileBackground(void) {
    pid_t childpid;

    if (server.bgrewritechildpid != -1) return REDIS_ERR;
    if ((childpid = fork()) == 0) {
        /* Child */
        char tmpfile[256];
        close(server.fd);

        snprintf(tmpfile,256,"temp-rewriteaof-bg-%d.aof", (int) getpid());
        if (rewriteAppendOnlyFile(tmpfile) == REDIS_OK) {
            exit(0);
        } else {
            exit(1);
        }
    } else {
        /* Parent */
        if (childpid == -1) {
            redisLog(REDIS_WARNING,
                "Can't rewrite append only file in background: fork: %s",
                strerror(errno));
            return REDIS_ERR;
        }
        redisLog(REDIS_NOTICE,
            "Background append only file rewriting started by pid %d",childpid);
        server.bgrewritechildpid = childpid;
        return REDIS_OK;
    }
    return REDIS_OK; /* unreached */
}

static void bgrewriteaofCommand(redisClient *c) {
    if (server.bgrewritechildpid != -1) {
        addReplySds(c,sdsnew("-ERR background append only file rewriting already in progress\r\n"));
        return;
    }
    if (rewriteAppendOnlyFileBackground() == REDIS_OK) {
        addReply(c,shared.ok);
    } else {
        addReply(c,shared.err);
    }
}

static void aofRemoveTempFile(pid_t childpid) {
    char tmpfile[256];

    snprintf(tmpfile,256,"temp-rewriteaof-bg-%d.aof", (int) childpid);
    unlink(tmpfile);
}

/* ================================= Debugging ============================== */

static void debugCommand(redisClient *c) {

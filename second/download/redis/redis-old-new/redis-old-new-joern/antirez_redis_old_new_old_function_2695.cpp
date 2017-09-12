void migrateCommand(redisClient *c) {
    int fd;
    long timeout;
    long dbid;
    char buf[64];
    FILE *fp;
    time_t ttl;
    robj *o;
    unsigned char type;
    off_t payload_len;

    /* Sanity check */
    if (getLongFromObjectOrReply(c,c->argv[5],&timeout,NULL) != REDIS_OK)
        return;
    if (getLongFromObjectOrReply(c,c->argv[4],&dbid,NULL) != REDIS_OK)
        return;
    if (timeout <= 0) timeout = 1;

    /* Check if the key is here. If not we reply with success as there is
     * nothing to migrate (for instance the key expired in the meantime), but
     * we include such information in the reply string. */
    if ((o = lookupKeyRead(c->db,c->argv[3])) == NULL) {
        addReplySds(c,sdsnew("+NOKEY"));
        return;
    }
    
    /* Connect */
    fd = anetTcpNonBlockConnect(server.neterr,c->argv[1]->ptr,
                atoi(c->argv[2]->ptr));
    if (fd == -1) {
        addReplyErrorFormat(c,"Can't connect to target node: %s",
            server.neterr);
        return;
    }
    if ((aeWait(fd,AE_WRITABLE,timeout*1000) & AE_WRITABLE) == 0) {
        addReplyError(c,"Timeout connecting to the client");
        return;
    }

    /* Create temp file */
    snprintf(buf,sizeof(buf),"redis-migrate-%d.tmp",getpid());
    fp = fopen(buf,"w+");
    if (!fp) {
        redisLog(REDIS_WARNING,"Can't open tmp file for MIGRATE: %s",
            strerror(errno));
        addReplyErrorFormat(c,"MIGRATE failed, tmp file creation error: %s.",
            strerror(errno));
        return;
    }
    unlink(buf);

    /* Build the SELECT + RESTORE query writing it in our temp file. */
    if (fwriteBulkCount(fp,'*',2) == 0) goto file_wr_err;
    if (fwriteBulkString(fp,"SELECT",6) == 0) goto file_wr_err;
    if (fwriteBulkLongLong(fp,dbid) == 0) goto file_wr_err;

    ttl = getExpire(c->db,c->argv[3]);
    type = o->type;
    if (fwriteBulkCount(fp,'*',4) == 0) goto file_wr_err;
    if (fwriteBulkString(fp,"RESTORE",7) == 0) goto file_wr_err;
    if (fwriteBulkObject(fp,c->argv[3]) == 0) goto file_wr_err;
    if (fwriteBulkLongLong(fp, (ttl == -1) ? 0 : ttl) == 0) goto file_wr_err;

    /* Finally the last argument that is the serailized object payload
     * in the form: <type><rdb-serailized-object>. */
    payload_len = rdbSavedObjectLen(o);
    if (fwriteBulkCount(fp,'$',payload_len+1) == 0) goto file_wr_err;
    if (fwrite(&type,1,1,fp) == 0) goto file_wr_err;
    if (rdbSaveObject(fp,o) == -1) goto file_wr_err;
    if (fwrite("\r\n",2,1,fp) == 0) goto file_wr_err;

    /* Tranfer the query to the other node */
    rewind(fp);
    {
        char buf[4096];
        size_t nread;

        while ((nread = fread(buf,1,sizeof(buf),fp)) != 0) {
            int nwritten;

            nwritten = syncWrite(fd,buf,nread,timeout);
            if (nwritten != (signed)nread) goto socket_wr_err;
        }
        if (ferror(fp)) goto file_rd_err;
    }

    /* Read back the reply */
    {
        char buf1[1024];
        char buf2[1024];

        /* Read the two replies */
        if (syncReadLine(fd, buf1, sizeof(buf1), timeout) <= 0)
            goto socket_rd_err;
        if (syncReadLine(fd, buf2, sizeof(buf2), timeout) <= 0)
                goto socket_rd_err;
        if (buf1[0] == '-' || buf2[0] == '-') {
            addReplyErrorFormat(c,"Target instance replied with error: %s",
                (buf1[0] == '-') ? buf1+1 : buf2+1);
        } else {
            dbDelete(c->db,c->argv[3]);
            addReply(c,shared.ok);
        }
    }
    fclose(fp);
    close(fd);
    return;

file_wr_err:
    redisLog(REDIS_WARNING,"Can't write on tmp file for MIGRATE: %s",
        strerror(errno));
    addReplyErrorFormat(c,"MIGRATE failed, tmp file write error: %s.",
        strerror(errno));
    fclose(fp);
    close(fd);
    return;

file_rd_err:
    redisLog(REDIS_WARNING,"Can't read from tmp file for MIGRATE: %s",
        strerror(errno));
    addReplyErrorFormat(c,"MIGRATE failed, tmp file read error: %s.",
        strerror(errno));
    fclose(fp);
    close(fd);
    return;

socket_wr_err:
    redisLog(REDIS_NOTICE,"Can't write to target node for MIGRATE: %s",
        strerror(errno));
    addReplyErrorFormat(c,"MIGRATE failed, writing to target node: %s.",
        strerror(errno));
    fclose(fp);
    close(fd);
    return;

socket_rd_err:
    redisLog(REDIS_NOTICE,"Can't read from target node for MIGRATE: %s",
        strerror(errno));
    addReplyErrorFormat(c,"MIGRATE failed, reading from target node: %s.",
        strerror(errno));
    fclose(fp);
    close(fd);
    return;
}
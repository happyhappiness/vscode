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

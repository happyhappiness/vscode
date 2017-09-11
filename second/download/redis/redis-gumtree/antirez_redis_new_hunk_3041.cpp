        return;
    }

    cmd = rioInitWithBuffer(sdsempty());
    redisAssert(rioWriteBulkCount(&cmd,'*',2));
    redisAssert(rioWriteBulkString(&cmd,"SELECT",6));
    redisAssert(rioWriteBulkLongLong(&cmd,dbid));

    ttl = getExpire(c->db,c->argv[3]);
    redisAssert(rioWriteBulkCount(&cmd,'*',4));
    redisAssert(rioWriteBulkString(&cmd,"RESTORE",7));
    redisAssert(c->argv[3]->encoding == REDIS_ENCODING_RAW);
    redisAssert(rioWriteBulkString(&cmd,c->argv[3]->ptr,sdslen(c->argv[3]->ptr)));
    redisAssert(rioWriteBulkLongLong(&cmd,(ttl == -1) ? 0 : ttl));

    /* Finally the last argument that is the serailized object payload
     * in the form: <type><rdb-serialized-object>. */
    payload = rioInitWithBuffer(sdsempty());
    redisAssert(rdbSaveObjectType(&payload,o));
    redisAssert(rdbSaveObject(&payload,o) != -1);
    redisAssert(rioWriteBulkString(&cmd,payload.io.buffer.ptr,sdslen(payload.io.buffer.ptr)));
    sdsfree(payload.io.buffer.ptr);

    /* Tranfer the query to the other node in 64K chunks. */
    {
        sds buf = cmd.io.buffer.ptr;
        size_t pos = 0, towrite;
        int nwritten = 0;

        while ((towrite = sdslen(buf)-pos) > 0) {
            towrite = (towrite > (64*1024) ? (64*1024) : towrite);
            nwritten = syncWrite(fd,buf+nwritten,towrite,timeout);
            if (nwritten != (signed)towrite) goto socket_wr_err;
            pos += nwritten;
        }
    }

    /* Read back the reply. */
    {
        char buf1[1024];
        char buf2[1024];

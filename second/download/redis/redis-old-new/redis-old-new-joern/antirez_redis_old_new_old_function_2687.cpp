void restoreCommand(redisClient *c) {
    FILE *fp;
    char buf[64];
    robj *o;
    unsigned char *data;
    long ttl;

    /* Make sure this key does not already exist here... */
    if (lookupKeyWrite(c->db,c->argv[1]) != NULL) {
        addReplyError(c,"Target key name is busy.");
        return;
    }

    /* Check if the TTL value makes sense */
    if (getLongFromObjectOrReply(c,c->argv[2],&ttl,NULL) != REDIS_OK) {
        return;
    } else if (ttl < 0) {
        addReplyError(c,"Invalid TTL value, must be >= 0");
        return;
    }

    /* rdbLoadObject() only works against file descriptors so we need to
     * dump the serialized object into a file and reload. */
    snprintf(buf,sizeof(buf),"redis-restore-%d.tmp",getpid());
    fp = fopen(buf,"w+");
    if (!fp) {
        redisLog(REDIS_WARNING,"Can't open tmp file for RESTORE: %s",
            strerror(errno));
        addReplyErrorFormat(c,"RESTORE failed, tmp file creation error: %s",
            strerror(errno));
        return;
    }
    unlink(buf);

    /* Write the actual data and rewind the file */
    data = (unsigned char*) c->argv[3]->ptr;
    if (fwrite(data+1,sdslen((sds)data)-1,1,fp) != 1) {
        redisLog(REDIS_WARNING,"Can't write against tmp file for RESTORE: %s",
            strerror(errno));
        addReplyError(c,"RESTORE failed, tmp file I/O error.");
        fclose(fp);
        return;
    }
    rewind(fp);

    /* Finally create the object from the serialized dump and
     * store it at the specified key. */
    if ((data[0] > 4 && data[0] < 9) ||
         data[0] > 11 ||
        (o = rdbLoadObject(data[0],fp)) == NULL)
    {
        addReplyError(c,"Bad data format.");
        fclose(fp);
        return;
    }
    fclose(fp);

    /* Create the key and set the TTL if any */
    dbAdd(c->db,c->argv[1],o);
    if (ttl) setExpire(c->db,c->argv[1],time(NULL)+ttl);
    addReply(c,shared.ok);
}
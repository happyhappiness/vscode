
int processMultibulkBuffer(redisClient *c) {
    char *newline = NULL;
    char *eptr;
    int pos = 0, tolerr;
    long bulklen;

    if (c->multibulklen == 0) {
        /* The client should have been reset */
        redisAssert(c->argc == 0);

        /* Multi bulk length cannot be read without a \r\n */
        newline = strstr(c->querybuf,"\r\n");
        if (newline == NULL)
            return REDIS_ERR;

        /* We know for sure there is a whole line since newline != NULL,
         * so go ahead and find out the multi bulk length. */
        redisAssert(c->querybuf[0] == '*');
        c->multibulklen = strtol(c->querybuf+1,&eptr,10);
        pos = (newline-c->querybuf)+2;
        if (c->multibulklen <= 0) {
            c->querybuf = sdsrange(c->querybuf,pos,-1);
            return REDIS_OK;
        } else if (c->multibulklen > 1024*1024) {
            addReplyError(c,"Protocol error: invalid multibulk length");
            setProtocolError(c,pos);
            return REDIS_ERR;
        }

        /* Setup argv array on client structure */
        if (c->argv) zfree(c->argv);
        c->argv = zmalloc(sizeof(robj*)*c->multibulklen);

        /* Search new newline */
        newline = strstr(c->querybuf+pos,"\r\n");
    }

    redisAssert(c->multibulklen > 0);
    while(c->multibulklen) {
        /* Read bulk length if unknown */
        if (c->bulklen == -1) {
            newline = strstr(c->querybuf+pos,"\r\n");
            if (newline != NULL) {
                if (c->querybuf[pos] != '$') {
                    addReplyErrorFormat(c,
                        "Protocol error: expected '$', got '%c'",
                        c->querybuf[pos]);
                    setProtocolError(c,pos);
                    return REDIS_ERR;
                }

                bulklen = strtol(c->querybuf+pos+1,&eptr,10);
                tolerr = (eptr[0] != '\r');
                if (tolerr || bulklen == LONG_MIN || bulklen == LONG_MAX ||
                    bulklen < 0 || bulklen > 512*1024*1024)
                {
                    addReplyError(c,"Protocol error: invalid bulk length");
                    setProtocolError(c,pos);
                    return REDIS_ERR;
                }
                pos += eptr-(c->querybuf+pos)+2;
                c->bulklen = bulklen;
            } else {
                /* No newline in current buffer, so wait for more data */
                break;
            }
        }

        /* Read bulk argument */

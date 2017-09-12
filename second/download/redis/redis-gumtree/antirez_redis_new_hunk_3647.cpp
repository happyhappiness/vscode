    }
}

int processInlineBuffer(redisClient *c) {
    char *newline = strstr(c->querybuf,"\r\n");
    int argc, j;
    sds *argv;
    size_t querylen;

    /* Nothing to do without a \r\n */
    if (newline == NULL)
        return REDIS_ERR;

    /* Split the input buffer up to the \r\n */
    querylen = newline-(c->querybuf);
    argv = sdssplitlen(c->querybuf,querylen," ",1,&argc);

    /* Leave data after the first line of the query in the buffer */
    c->querybuf = sdsrange(c->querybuf,querylen+2,-1);

    /* Setup argv array on client structure */
    if (c->argv) zfree(c->argv);
    c->argv = zmalloc(sizeof(robj*)*argc);

    /* Create redis objects for all arguments. */
    for (c->argc = 0, j = 0; j < argc; j++) {
        if (sdslen(argv[j])) {
            c->argv[c->argc] = createObject(REDIS_STRING,argv[j]);
            c->argc++;
        } else {
            sdsfree(argv[j]);
        }
    }
    zfree(argv);
    return REDIS_OK;
}

/* Helper function. Trims query buffer to make the function that processes
 * multi bulk requests idempotent. */
static void setProtocolError(redisClient *c, int pos) {
    c->flags |= REDIS_CLOSE_AFTER_REPLY;
    c->querybuf = sdsrange(c->querybuf,pos,-1);
}

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
                    bulklen < 0 || bulklen > 1024*1024*1024)
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
        if (sdslen(c->querybuf)-pos < (unsigned)(c->bulklen+2)) {
            /* Not enough data (+2 == trailing \r\n) */
            break;
        } else {
            c->argv[c->argc++] = createStringObject(c->querybuf+pos,c->bulklen);
            pos += c->bulklen+2;
            c->bulklen = -1;
            c->multibulklen--;
        }
    }

    /* Trim to pos */
    c->querybuf = sdsrange(c->querybuf,pos,-1);

    /* We're done when c->multibulk == 0 */
    if (c->multibulklen == 0) {
        return REDIS_OK;
    }
    return REDIS_ERR;
}

void processInputBuffer(redisClient *c) {
    /* Keep processing while there is something in the input buffer */
    while(sdslen(c->querybuf)) {
        /* Before to process the input buffer, make sure the client is not
         * waitig for a blocking operation such as BLPOP. Note that the first
         * iteration the client is never blocked, otherwise the processInputBuffer
         * would not be called at all, but after the execution of the first commands
         * in the input buffer the client may be blocked, and the "goto again"
         * will try to reiterate. The following line will make it return asap. */
        if (c->flags & REDIS_BLOCKED || c->flags & REDIS_IO_WAIT) return;

        /* Never continue to process the input buffer after QUIT. After the output
         * buffer is flushed (with the OK), the connection will be dropped. */
        if (c->flags & REDIS_QUIT) return;

        /* Determine request type when unknown. */
        if (!c->reqtype) {
            if (c->querybuf[0] == '*') {
                c->reqtype = REDIS_REQ_MULTIBULK;
            } else {
                c->reqtype = REDIS_REQ_INLINE;
            }
        }

        if (c->reqtype == REDIS_REQ_INLINE) {
            if (processInlineBuffer(c) != REDIS_OK) break;
        } else if (c->reqtype == REDIS_REQ_MULTIBULK) {
            if (processMultibulkBuffer(c) != REDIS_OK) break;
        } else {
            redisPanic("Unknown request type");
        }

        /* Multibulk processing could see a <= 0 length. */
        if (c->argc > 0)
            processCommand(c);
        resetClient(c);
    }
}


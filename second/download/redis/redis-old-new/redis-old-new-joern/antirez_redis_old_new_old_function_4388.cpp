static void readQueryFromClient(aeEventLoop *el, int fd, void *privdata, int mask) {
    redisClient *c = (redisClient*) privdata;
    char buf[REDIS_IOBUF_LEN];
    int nread;
    REDIS_NOTUSED(el);
    REDIS_NOTUSED(mask);

    nread = read(fd, buf, REDIS_IOBUF_LEN);
    if (nread == -1) {
        if (errno == EAGAIN) {
            nread = 0;
        } else {
            redisLog(REDIS_DEBUG, "Reading from client: %s",strerror(errno));
            freeClient(c);
            return;
        }
    } else if (nread == 0) {
        redisLog(REDIS_DEBUG, "Client closed connection");
        freeClient(c);
        return;
    }
    if (nread) {
        c->querybuf = sdscatlen(c->querybuf, buf, nread);
        c->lastinteraction = time(NULL);
    } else {
        return;
    }

again:
    if (c->bulklen == -1) {
        /* Read the first line of the query */
        char *p = strchr(c->querybuf,'\n');
        size_t querylen;

        if (p) {
            sds query, *argv;
            int argc, j;
            
            query = c->querybuf;
            c->querybuf = sdsempty();
            querylen = 1+(p-(query));
            if (sdslen(query) > querylen) {
                /* leave data after the first line of the query in the buffer */
                c->querybuf = sdscatlen(c->querybuf,query+querylen,sdslen(query)-querylen);
            }
            *p = '\0'; /* remove "\n" */
            if (*(p-1) == '\r') *(p-1) = '\0'; /* and "\r" if any */
            sdsupdatelen(query);

            /* Now we can split the query in arguments */
            if (sdslen(query) == 0) {
                /* Ignore empty query */
                sdsfree(query);
                return;
            }
            argv = sdssplitlen(query,sdslen(query)," ",1,&argc);
            if (argv == NULL) oom("sdssplitlen");
            sdsfree(query);

            if (c->argv) zfree(c->argv);
            c->argv = zmalloc(sizeof(robj*)*argc);
            if (c->argv == NULL) oom("allocating arguments list for client");

            for (j = 0; j < argc; j++) {
                if (sdslen(argv[j])) {
                    c->argv[c->argc] = createObject(REDIS_STRING,argv[j]);
                    c->argc++;
                } else {
                    sdsfree(argv[j]);
                }
            }
            zfree(argv);
            /* Execute the command. If the client is still valid
             * after processCommand() return and there is something
             * on the query buffer try to process the next command. */
            if (c->argc && processCommand(c) && sdslen(c->querybuf)) goto again;
            return;
        } else if (sdslen(c->querybuf) >= REDIS_REQUEST_MAX_SIZE) {
            redisLog(REDIS_DEBUG, "Client protocol error");
            freeClient(c);
            return;
        }
    } else {
        /* Bulk read handling. Note that if we are at this point
           the client already sent a command terminated with a newline,
           we are reading the bulk data that is actually the last
           argument of the command. */
        int qbl = sdslen(c->querybuf);

        if (c->bulklen <= qbl) {
            /* Copy everything but the final CRLF as final argument */
            c->argv[c->argc] = createStringObject(c->querybuf,c->bulklen-2);
            c->argc++;
            c->querybuf = sdsrange(c->querybuf,c->bulklen,-1);
            processCommand(c);
            return;
        }
    }
}
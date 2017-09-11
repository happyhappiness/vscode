    /* Suppress hiredis cleanup of unused buffers for max speed. */
    c->context->reader->maxbuf = 0;

    /* Queue N requests accordingly to the pipeline size. */
    c->obuf = sdsempty();
    if (config.dbnum != 0) {
        /* If a DB number different than zero is selected, prefix our request
         * buffer with the SELECT command, that will be discarded the first
         * time the replies are received, so if the client is reused the
         * SELECT command will not be used again. */
        c->obuf = sdscatprintf(c->obuf,"*2\r\n$6\r\nSELECT\r\n$%d\r\n%s\r\n",
            (int)sdslen(config.dbnumstr),config.dbnumstr);
        c->selectlen = sdslen(c->obuf);
    } else {
        c->selectlen = 0;
    }
    for (j = 0; j < config.pipeline; j++)
        c->obuf = sdscatlen(c->obuf,cmd,len);
    c->randlen = 0;
    c->randfree = RANDPTR_INITIAL_SIZE;
    c->randptr = zmalloc(sizeof(char*)*c->randfree);
    c->written = 0;
    c->pending = config.pipeline;
    if (c->selectlen) c->pending++;

    /* Find substrings in the output buffer that need to be randomized. */
    if (config.randomkeys) {
        char *p = c->obuf;
        while ((p = strstr(p,":rand:")) != NULL) {
            if (c->randfree == 0) {
                c->randptr = zrealloc(c->randptr,sizeof(char*)*c->randlen*2);
                c->randfree += c->randlen;
            }
            c->randptr[c->randlen++] = p+6;
            c->randfree--;
            p += 6;
        }
    }
    aeCreateFileEvent(config.el,c->context->fd,AE_WRITABLE,writeHandler,c);

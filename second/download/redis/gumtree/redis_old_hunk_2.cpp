        else
            fprintf(stderr,"%s: %s\n",config.hostsocket,c->context->errstr);
        exit(1);
    }
    /* Suppress hiredis cleanup of unused buffers for max speed. */
    c->context->reader->maxbuf = 0;
    /* Queue N requests accordingly to the pipeline size. */
    c->obuf = sdsempty();
    for (j = 0; j < config.pipeline; j++)
        c->obuf = sdscatlen(c->obuf,cmd,len);
    c->randlen = 0;
    c->written = 0;
    c->pending = config.pipeline;

    /* Find substrings in the output buffer that need to be randomized. */
    if (config.randomkeys) {
        char *p = c->obuf;
        while ((p = strstr(p,":rand:")) != NULL) {
            assert(c->randlen < (signed)(sizeof(c->randptr)/sizeof(char*)));
            c->randptr[c->randlen++] = p+6;
            p += 6;
        }
    }

/*    redisSetReplyObjectFunctions(c->context,NULL); */
    aeCreateFileEvent(config.el,c->context->fd,AE_WRITABLE,writeHandler,c);
    listAddNodeTail(config.clients,c);
    config.liveclients++;
    return c;
}

static void createMissingClients(client c) {
    int n = 0;

    while(config.liveclients < config.numclients) {
        createClient(c->obuf,sdslen(c->obuf)/config.pipeline);

        /* Listen backlog is quite limited on most systems */
        if (++n > 64) {
            usleep(50000);
            n = 0;
        }

            fprintf(stderr,"%s: %s\n",config.hostsocket,c->context->errstr);
        exit(1);
    }
    /* Queue N requests accordingly to the pipeline size. */
    c->obuf = sdsempty();
    for (j = 0; j < config.pipeline; j++)
        c->obuf = sdscatlen(c->obuf,cmd,len);
    c->randlen = 0;
    c->written = 0;
    c->pending = config.pipeline;

    /* Find substrings in the output buffer that need to be randomized. */
    if (config.randomkeys) {

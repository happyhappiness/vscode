            fprintf(stderr,"%s: %s\n",config.hostsocket,c->context->errstr);
        exit(1);
    }
    c->obuf = sdsnewlen(cmd,len);
    c->randlen = 0;
    c->written = 0;

    /* Find substrings in the output buffer that need to be randomized. */
    if (config.randomkeys) {
        char *p = c->obuf, *newline;
        while ((p = strstr(p,":rand:")) != NULL) {
            newline = strstr(p,"\r\n");
            assert(newline-(p+6) == 12); /* 12 chars for randomness */
            assert(c->randlen < (signed)(sizeof(c->randptr)/sizeof(char*)));
            c->randptr[c->randlen++] = p+6;
            p = newline+2;
        }
    }

    redisSetReplyObjectFunctions(c->context,NULL);
    aeCreateFileEvent(config.el,c->context->fd,AE_WRITABLE,writeHandler,c);
    listAddNodeTail(config.clients,c);

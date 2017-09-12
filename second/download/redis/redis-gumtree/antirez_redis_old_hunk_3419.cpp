            fprintf(stderr,"%s: %s\n",config.hostsocket,c->context->errstr);
        exit(1);
    }
    c->replytype = replytype;
    c->state = CLIENT_CONNECTING;
    c->obuf = sdsempty();
    c->written = 0;
    redisSetReplyObjectFunctions(c->context,NULL);
    aeCreateFileEvent(config.el,c->context->fd,AE_WRITABLE,writeHandler,c);
    listAddNodeTail(config.clients,c);

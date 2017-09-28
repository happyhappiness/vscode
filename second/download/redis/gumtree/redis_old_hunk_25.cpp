                server.masterhost, server.masterport);
        else
            buf[0] = '\0';
        addReplyBulkCString(c,buf);
        matches++;
    }
    setDeferredMultiBulkLength(c,replylen,matches*2);
}

void configCommand(redisClient *c) {
    if (!strcasecmp(c->argv[1]->ptr,"set")) {
        if (c->argc != 4) goto badarity;
        configSetCommand(c);
    } else if (!strcasecmp(c->argv[1]->ptr,"get")) {
        if (c->argc != 3) goto badarity;

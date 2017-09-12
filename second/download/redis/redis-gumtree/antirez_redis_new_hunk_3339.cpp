    }
    info = sdscat(info,"\r\n");

    numcommands = sizeof(readonlyCommandTable)/sizeof(struct redisCommand);
    for (j = 0; j < numcommands; j++) {
        struct redisCommand *c = readonlyCommandTable+j;
        info = sdscatprintf(info,"command_%s:microseconds:%lld\r\n",
            c->name, c->microseconds);
    }

    for (j = 0; j < server.dbnum; j++) {
        long long keys, vkeys;


    }
}

void commandCommand(redisClient *c) {
    dictIterator *di;
    dictEntry *de;

    if (c->argc > 2 && !strcasecmp(c->argv[1]->ptr, "info")) {
        int i;
        addReplyMultiBulkLen(c, c->argc-2);
        for (i = 2; i < c->argc; i++) {
            addReplyCommand(c, dictFetchValue(server.commands, c->argv[i]->ptr));
        }
    } else if (c->argc > 2) {
        addReplyError(c, "Unknown subcommand.");
        return;
    } else {
        addReplyMultiBulkLen(c, dictSize(server.commands));
        di = dictGetIterator(server.commands);
        while ((de = dictNext(di)) != NULL) {
            addReplyCommand(c, dictGetVal(de));
        }
        dictReleaseIterator(di);
    }
}


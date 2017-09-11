        int i;
        addReplyMultiBulkLen(c, c->argc-2);
        for (i = 2; i < c->argc; i++) {
            replyCmd(c, dictFetchValue(server.commands, c->argv[i]->ptr));
        }
    } else if (c->argc > 2) {
        addReplyError(c, "Unknown subcommand.");

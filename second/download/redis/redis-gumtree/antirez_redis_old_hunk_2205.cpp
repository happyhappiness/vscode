
        if (c->argc != 2) goto numargserr;
        sentinelPendingScriptsCommand(c);
    } else {
        addReplyErrorFormat(c,"Unknown sentinel subcommand '%s'",
                               (char*)c->argv[1]->ptr);

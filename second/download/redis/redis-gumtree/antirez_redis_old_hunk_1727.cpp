    } else if (!strcasecmp(c->argv[1]->ptr,"set")) {
        if (c->argc < 3 || c->argc % 2 == 0) goto numargserr;
        sentinelSetCommand(c);
    } else {
        addReplyErrorFormat(c,"Unknown sentinel subcommand '%s'",
                               (char*)c->argv[1]->ptr);

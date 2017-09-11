    {
        server.active_expire_enabled = atoi(c->argv[2]->ptr);
        addReply(c,shared.ok);
    } else {
        addReplyErrorFormat(c, "Unknown DEBUG subcommand or wrong number of arguments for '%s'",
            (char*)c->argv[1]->ptr);

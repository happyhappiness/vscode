    if (!cmd) {
        addReplyErrorFormat(c,"unknown command '%s'",
            (char*)c->argv[0]->ptr);
        return REDIS_OK;
    } else if ((cmd->arity > 0 && cmd->arity != c->argc) ||
               (c->argc < -cmd->arity)) {
        addReplyErrorFormat(c,"wrong number of arguments for '%s' command",
            cmd->name);
        return REDIS_OK;
    }

    /* Let's try to encode the bulk object to save space. */
    if (cmd->flags & REDIS_CMD_BULK)
        c->argv[c->argc-1] = tryObjectEncoding(c->argv[c->argc-1]);

    /* Check if the user is authenticated */
    if (server.requirepass && !c->authenticated && cmd->proc != authCommand) {
        addReplyError(c,"operation not permitted");
        return REDIS_OK;
    }

    /* Handle the maxmemory directive.

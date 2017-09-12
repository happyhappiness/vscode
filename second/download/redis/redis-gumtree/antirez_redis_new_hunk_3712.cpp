     * such wrong arity, bad command name and so forth. */
    cmd = lookupCommand(c->argv[0]->ptr);
    if (!cmd) {
        addReplyErrorFormat(c,"unknown command '%s'",
            (char*)c->argv[0]->ptr);
        resetClient(c);
        return 1;
    } else if ((cmd->arity > 0 && cmd->arity != c->argc) ||
               (c->argc < -cmd->arity)) {
        addReplyErrorFormat(c,"wrong number of arguments for '%s' command",
            cmd->name);
        resetClient(c);
        return 1;
    } else if (cmd->flags & REDIS_CMD_BULK && c->bulklen == -1) {
        /* This is a bulk command, we have to read the last argument yet. */
        char *eptr;
        long bulklen = strtol(c->argv[c->argc-1]->ptr,&eptr,10);
        int perr = eptr[0] != '\0';

        decrRefCount(c->argv[c->argc-1]);
        if (perr || bulklen == LONG_MAX || bulklen == LONG_MIN ||
            bulklen < 0 || bulklen > 1024*1024*1024)
        {
            c->argc--;
            addReplyError(c,"invalid bulk write count");
            resetClient(c);
            return 1;
        }

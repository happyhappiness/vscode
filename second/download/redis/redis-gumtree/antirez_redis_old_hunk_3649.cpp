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
        c->argc--;
        c->bulklen = bulklen+2; /* add two bytes for CR+LF */
        /* It is possible that the bulk read is already in the
         * buffer. Check this condition and handle it accordingly.
         * This is just a fast path, alternative to call processInputBuffer().
         * It's a good idea since the code is small and this condition
         * happens most of the times. */
        if ((signed)sdslen(c->querybuf) >= c->bulklen) {
            c->argv[c->argc] = createStringObject(c->querybuf,c->bulklen-2);
            c->argc++;
            c->querybuf = sdsrange(c->querybuf,c->bulklen,-1);
        } else {
            /* Otherwise return... there is to read the last argument
             * from the socket. */
            return 1;
        }
    }
    /* Let's try to encode the bulk object to save space. */
    if (cmd->flags & REDIS_CMD_BULK)
        c->argv[c->argc-1] = tryObjectEncoding(c->argv[c->argc-1]);

    /* Check if the user is authenticated */
    if (server.requirepass && !c->authenticated && cmd->proc != authCommand) {
        addReplyError(c,"operation not permitted");
        resetClient(c);
        return 1;
    }

    /* Handle the maxmemory directive.

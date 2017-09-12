
    /* Check if the user is authenticated */
    if (server.requirepass && !c->authenticated && cmd->proc != authCommand) {
        addReplyError(c,"operation not permitted");
        resetClient(c);
        return 1;
    }

    /* Handle the maxmemory directive.
     *
     * First we try to free some memory if possible (if there are volatile
     * keys in the dataset). If there are not the only thing we can do
     * is returning an error. */
    if (server.maxmemory) freeMemoryIfNeeded();
    if (server.maxmemory && (cmd->flags & REDIS_CMD_DENYOOM) &&
        zmalloc_used_memory() > server.maxmemory)
    {
        addReplyError(c,"command not allowed when used memory > 'maxmemory'");
        resetClient(c);
        return 1;
    }

     * keys in the dataset). If there are not the only thing we can do
     * is returning an error. */
    if (server.maxmemory) freeMemoryIfNeeded();
    if (server.maxmemory && (cmd->flags & REDIS_CMD_DENYOOM) &&
        zmalloc_used_memory() > server.maxmemory)
    {
        addReplyError(c,"command not allowed when used memory > 'maxmemory'");

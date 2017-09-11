     * First we try to free some memory if possible (if there are volatile
     * keys in the dataset). If there are not the only thing we can do
     * is returning an error. */
    if (server.maxmemory) {
        int retval = freeMemoryIfNeeded();
        if ((c->cmd->flags & REDIS_CMD_DENYOOM) && retval == REDIS_ERR) {
            addReplyError(c,
                "command not allowed when used memory > 'maxmemory'");
            return REDIS_OK;
        }
    }

    /* Only allow SUBSCRIBE and UNSUBSCRIBE in the context of Pub/Sub */

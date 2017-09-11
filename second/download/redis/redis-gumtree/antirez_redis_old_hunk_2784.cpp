    if (server.maxmemory) {
        int retval = freeMemoryIfNeeded();
        if ((c->cmd->flags & REDIS_CMD_DENYOOM) && retval == REDIS_ERR) {
            addReplyError(c,
                "command not allowed when used memory > 'maxmemory'");
            return REDIS_OK;
        }
    }

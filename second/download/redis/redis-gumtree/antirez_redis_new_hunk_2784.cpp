    if (server.maxmemory) {
        int retval = freeMemoryIfNeeded();
        if ((c->cmd->flags & REDIS_CMD_DENYOOM) && retval == REDIS_ERR) {
            addReply(c, shared.oomerr);
            return REDIS_OK;
        }
    }

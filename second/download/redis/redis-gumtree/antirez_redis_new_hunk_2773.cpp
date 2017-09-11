    if (server.maxmemory) {
        int retval = freeMemoryIfNeeded();
        if ((c->cmd->flags & REDIS_CMD_DENYOOM) && retval == REDIS_ERR) {
            addReply(c, shared.oomerr);
            return REDIS_OK;
        }
    }

    /* Don't accept write commands if there are problems persisting on disk. */
    if (server.stop_writes_on_bgsave_err &&
        server.saveparamslen > 0
        && server.lastbgsave_status == REDIS_ERR &&
        c->cmd->flags & REDIS_CMD_WRITE)
    {
        addReply(c, shared.bgsaveerr);
        return REDIS_OK;
    }

    /* Don't accept wirte commands if this is a read only slave. But
     * accept write commands if this is our master. */
    if (server.masterhost && server.repl_slave_ro &&
        !(c->flags & REDIS_MASTER) &&
        c->cmd->flags & REDIS_CMD_WRITE)
    {
        addReply(c, shared.roslaveerr);
        return REDIS_OK;
    }

    /* Only allow SUBSCRIBE and UNSUBSCRIBE in the context of Pub/Sub */
    if ((dictSize(c->pubsub_channels) > 0 || listLength(c->pubsub_patterns) > 0)
        &&

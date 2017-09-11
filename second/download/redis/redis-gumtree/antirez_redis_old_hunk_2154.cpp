
    /* Don't accept write commands if there are problems persisting on disk
     * and if this is a master instance. */
    if (server.stop_writes_on_bgsave_err &&
        server.saveparamslen > 0
        && server.lastbgsave_status == REDIS_ERR &&
        server.masterhost == NULL &&
        (c->cmd->flags & REDIS_CMD_WRITE ||
         c->cmd->proc == pingCommand))
    {
        flagTransaction(c);
        addReply(c, shared.bgsaveerr);
        return REDIS_OK;
    }


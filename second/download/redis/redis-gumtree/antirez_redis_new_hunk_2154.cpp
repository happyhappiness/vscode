
    /* Don't accept write commands if there are problems persisting on disk
     * and if this is a master instance. */
    if (((server.stop_writes_on_bgsave_err &&
          server.saveparamslen > 0 &&
          server.lastbgsave_status == REDIS_ERR) ||
          server.aof_last_write_status == REDIS_ERR) &&
        server.masterhost == NULL &&
        (c->cmd->flags & REDIS_CMD_WRITE ||
         c->cmd->proc == pingCommand))
    {
        flagTransaction(c);
        if (server.aof_last_write_status == REDIS_OK)
            addReply(c, shared.bgsaveerr);
        else
            addReplySds(c,
                sdscatprintf(sdsempty(),
                "-MISCONF Errors writing to the AOF file: %s\r\n",
                strerror(server.aof_last_write_errno)));
        return REDIS_OK;
    }


     * we are a slave with a broken link with master. */
    if (server.masterhost && server.replstate != REDIS_REPL_CONNECTED &&
        server.repl_serve_stale_data == 0 &&
        c->cmd->proc != infoCommand && c->cmd->proc != slaveofCommand)
    {
        addReplyError(c,
            "link with MASTER is down and slave-serve-stale-data is set to no");
        return REDIS_OK;
    }

    /* Loading DB? Return an error if the command is not INFO */
    if (server.loading && c->cmd->proc != infoCommand) {
        addReply(c, shared.loadingerr);
        return REDIS_OK;
    }

    /* Exec the command */
    if (c->flags & REDIS_MULTI &&
        c->cmd->proc != execCommand && c->cmd->proc != discardCommand &&
        c->cmd->proc != multiCommand && c->cmd->proc != watchCommand)
    {
        queueMultiCommand(c);
        addReply(c,shared.queued);
    } else {
        call(c);
    }
    return REDIS_OK;
}

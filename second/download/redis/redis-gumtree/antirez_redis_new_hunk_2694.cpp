        server.repl_serve_stale_data == 0 &&
        c->cmd->proc != infoCommand && c->cmd->proc != slaveofCommand)
    {
        addReply(c, shared.masterdownerr);
        return REDIS_OK;
    }


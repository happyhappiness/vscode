    if (server.requirepass && !c->authenticated && c->cmd->proc != authCommand)
    {
        flagTransaction(c);
        addReplyError(c,"operation not permitted");
        return REDIS_OK;
    }


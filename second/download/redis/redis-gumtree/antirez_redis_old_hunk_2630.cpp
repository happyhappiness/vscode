    /* Check if the user is authenticated */
    if (server.requirepass && !c->authenticated && c->cmd->proc != authCommand)
    {
        addReplyError(c,"operation not permitted");
        return REDIS_OK;
    }

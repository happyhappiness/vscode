
    /* Check if the user is authenticated */
    if (server.requirepass && !c->authenticated && cmd->proc != authCommand) {
        addReplyError(c,"operation not permitted");
        resetClient(c);
        return 1;
    }

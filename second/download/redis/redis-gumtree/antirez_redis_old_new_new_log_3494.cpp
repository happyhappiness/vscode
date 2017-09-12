(server.requirepass && !c->authenticated && cmd->proc != authCommand) {
        addReplyError(c,"operation not permitted");;
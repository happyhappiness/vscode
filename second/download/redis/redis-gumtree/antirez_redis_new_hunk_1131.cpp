        c->cmd->proc != psubscribeCommand &&
        c->cmd->proc != punsubscribeCommand) {
        addReplyError(c,"only (P)SUBSCRIBE / (P)UNSUBSCRIBE / QUIT allowed in this context");
        return C_OK;
    }

    /* Only allow INFO and SLAVEOF when slave-serve-stale-data is no and

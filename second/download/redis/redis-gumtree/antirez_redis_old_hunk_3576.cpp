        return REDIS_OK;
    }

    /* Exec the command */
    if (c->flags & REDIS_MULTI &&
        cmd->proc != execCommand && cmd->proc != discardCommand &&

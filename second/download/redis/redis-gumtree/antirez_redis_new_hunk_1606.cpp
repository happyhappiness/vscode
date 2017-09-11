            luaPushError(lua,"Unknown Redis command called from Lua script");
        goto cleanup;
    }
    c->cmd = cmd;

    /* There are commands that are not allowed inside scripts. */
    if (cmd->flags & REDIS_CMD_NOSCRIPT) {

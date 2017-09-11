            luaPushError(lua,"Unknown Redis command called from Lua script");
        goto cleanup;
    }
    c->cmd = c->lastcmd = cmd;

    /* There are commands that are not allowed inside scripts. */
    if (cmd->flags & CMD_NOSCRIPT) {

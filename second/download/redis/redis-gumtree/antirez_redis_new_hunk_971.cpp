    c->cmd = cmd;

    /* There are commands that are not allowed inside scripts. */
    if (cmd->flags & CMD_NOSCRIPT) {
        luaPushError(lua, "This Redis command is not allowed from scripts");
        goto cleanup;
    }

    /* Write commands are forbidden against read-only slaves, or if a
     * command marked as non-deterministic was already called in the context
     * of this script. */
    if (cmd->flags & CMD_WRITE) {
        if (server.lua_random_dirty) {
            luaPushError(lua,
                "Write commands not allowed after non deterministic commands");
            goto cleanup;
        } else if (server.masterhost && server.repl_slave_ro &&
                   !server.loading &&
                   !(server.lua_caller->flags & CLIENT_MASTER))
        {
            luaPushError(lua, shared.roslaveerr->ptr);
            goto cleanup;

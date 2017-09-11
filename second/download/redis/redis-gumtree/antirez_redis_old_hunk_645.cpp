     * command marked as non-deterministic was already called in the context
     * of this script. */
    if (cmd->flags & CMD_WRITE) {
        if (server.lua_random_dirty) {
            luaPushError(lua,
                "Write commands not allowed after non deterministic commands");
            goto cleanup;
        } else if (server.masterhost && server.repl_slave_ro &&
                   !server.loading &&

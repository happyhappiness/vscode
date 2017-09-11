    if (server.maxmemory && server.lua_write_dirty == 0 &&
        (cmd->flags & REDIS_CMD_DENYOOM))
    {
        if (freeMemoryIfNeeded() == C_ERR) {
            luaPushError(lua, shared.oomerr->ptr);
            goto cleanup;
        }

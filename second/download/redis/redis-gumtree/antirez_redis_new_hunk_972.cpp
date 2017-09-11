     * first write in the context of this script, otherwise we can't stop
     * in the middle. */
    if (server.maxmemory && server.lua_write_dirty == 0 &&
        (cmd->flags & CMD_DENYOOM))
    {
        if (freeMemoryIfNeeded() == C_ERR) {
            luaPushError(lua, shared.oomerr->ptr);
            goto cleanup;
        }
    }

    if (cmd->flags & CMD_RANDOM) server.lua_random_dirty = 1;
    if (cmd->flags & CMD_WRITE) server.lua_write_dirty = 1;

    /* If this is a Redis Cluster node, we need to make sure Lua is not
     * trying to access non-local keys, with the exception of commands
     * received from our master. */
    if (server.cluster_enabled && !(server.lua_caller->flags & CLIENT_MASTER)) {
        /* Duplicate relevant flags in the lua client. */
        c->flags &= ~(CLIENT_READONLY|CLIENT_ASKING);
        c->flags |= server.lua_caller->flags & (CLIENT_READONLY|CLIENT_ASKING);
        if (getNodeByQuery(c,c->cmd,c->argv,c->argc,NULL,NULL) !=
                           server.cluster->myself)
        {

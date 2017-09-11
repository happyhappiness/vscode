                "Write commands not allowed after non deterministic commands");
            goto cleanup;
        } else if (server.masterhost && server.repl_slave_ro &&
                   !(server.lua_caller->flags & REDIS_MASTER))
        {
            luaPushError(lua, shared.roslaveerr->ptr);

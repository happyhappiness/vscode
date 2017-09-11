        goto cleanup;
    }

    if (cmd->flags & REDIS_CMD_NOSCRIPT) {
        luaPushError(lua, "This Redis command is not allowed from scripts");
        goto cleanup;
    }

    if (cmd->flags & REDIS_CMD_WRITE && server.lua_random_dirty) {
        luaPushError(lua,
            "Write commands not allowed after non deterministic commands");
        goto cleanup;
    }

    if (cmd->flags & REDIS_CMD_RANDOM) server.lua_random_dirty = 1;

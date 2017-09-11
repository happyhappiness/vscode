        goto cleanup;
    }

    if (cmd->flags & REDIS_CMD_WRITE && server.lua_random_dirty) {
        luaPushError(lua,
            "Write commands not allowed after non deterministic commands");
        goto cleanup;
    }

    if (cmd->flags & REDIS_CMD_RANDOM) server.lua_random_dirty = 1;

    /* Run the command */
    cmd->proc(c);


    if (cmd->flags & REDIS_CMD_RANDOM) server.lua_random_dirty = 1;
    if (cmd->flags & REDIS_CMD_WRITE) server.lua_write_dirty = 1;

    /* Run the command */
    c->cmd = cmd;
    call(c,REDIS_CALL_SLOWLOG | REDIS_CALL_STATS);

    /* Convert the result of the Redis command into a suitable Lua type.

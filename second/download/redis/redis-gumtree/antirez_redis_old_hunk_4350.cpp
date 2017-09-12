        return 1;
    } else if ((cmd->arity > 0 && cmd->arity != c->argc) ||
               (c->argc < -cmd->arity)) {
        addReplySds(c,sdsnew("-ERR wrong number of arguments\r\n"));
        resetClient(c);
        return 1;
    } else if (server.maxmemory && cmd->flags & REDIS_CMD_DENYOOM && zmalloc_used_memory() > server.maxmemory) {

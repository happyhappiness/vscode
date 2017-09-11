            addReply(c,shared.err);
            return;
        }
        emptyDb(NULL);
        if (rdbLoad(server.rdb_filename) != REDIS_OK) {
            addReplyError(c,"Error trying to load the RDB dump");
            return;
        }
        redisLog(REDIS_WARNING,"DB reloaded by DEBUG RELOAD");
        addReply(c,shared.ok);
    } else if (!strcasecmp(c->argv[1]->ptr,"loadaof")) {
        emptyDb(NULL);
        if (loadAppendOnlyFile(server.aof_filename) != REDIS_OK) {
            addReply(c,shared.err);
            return;

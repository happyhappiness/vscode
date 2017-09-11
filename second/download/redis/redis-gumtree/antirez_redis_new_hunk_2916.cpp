        if (c->argc >= 3) c->argv[2] = tryObjectEncoding(c->argv[2]);
        redisAssertWithInfo(c,c->argv[0],1 == 2);
    } else if (!strcasecmp(c->argv[1]->ptr,"reload")) {
        if (rdbSave(server.rdb_filename) != REDIS_OK) {
            addReply(c,shared.err);
            return;
        }
        emptyDb();
        if (rdbLoad(server.rdb_filename) != REDIS_OK) {
            addReplyError(c,"Error trying to load the RDB dump");
            return;
        }

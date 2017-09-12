void debugCommand(redisClient *c) {
    if (!strcasecmp(c->argv[1]->ptr,"segfault")) {
        *((char*)-1) = 'x';
    } else if (!strcasecmp(c->argv[1]->ptr,"flushcache")) {
        if (!server.ds_enabled) {
            addReplyError(c, "DEBUG FLUSHCACHE called with diskstore off.");
            return;
        } else {
            emptyDb();
            addReply(c,shared.ok);
            return;
        }
    } else if (!strcasecmp(c->argv[1]->ptr,"reload")) {
        if (server.ds_enabled) {
            addReply(c,shared.ok);
            return;
        }
        if (rdbSave(server.dbfilename) != REDIS_OK) {
            addReply(c,shared.err);
            return;

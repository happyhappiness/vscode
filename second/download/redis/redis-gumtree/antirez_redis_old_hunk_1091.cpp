        sds stats = sdsempty();
        char buf[4096];

        if (getLongFromObjectOrReply(c, c->argv[2], &dbid, NULL) != REDIS_OK)
            return;
        if (dbid < 0 || dbid >= server.dbnum) {
            addReplyError(c,"Out of range database");

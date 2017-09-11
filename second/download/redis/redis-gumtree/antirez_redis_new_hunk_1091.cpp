        sds stats = sdsempty();
        char buf[4096];

        if (getLongFromObjectOrReply(c, c->argv[2], &dbid, NULL) != C_OK)
            return;
        if (dbid < 0 || dbid >= server.dbnum) {
            addReplyError(c,"Out of range database");

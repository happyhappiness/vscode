        zfree(ptr);
        addReply(c,shared.ok);
    } else if (!strcasecmp(c->argv[1]->ptr,"assert")) {
        if (c->argc >= 3) c->argv[2] = tryObjectEncoding(c->argv[2]);
        serverAssertWithInfo(c,c->argv[0],1 == 2);
    } else if (!strcasecmp(c->argv[1]->ptr,"reload")) {
        if (rdbSave(server.rdb_filename) != C_OK) {
            addReply(c,shared.err);
            return;
        }
        emptyDb(NULL);
        if (rdbLoad(server.rdb_filename) != C_OK) {
            addReplyError(c,"Error trying to load the RDB dump");
            return;
        }
        serverLog(LL_WARNING,"DB reloaded by DEBUG RELOAD");
        addReply(c,shared.ok);
    } else if (!strcasecmp(c->argv[1]->ptr,"loadaof")) {
        if (server.aof_state == AOF_ON) flushAppendOnlyFile(1);
        emptyDb(NULL);
        if (loadAppendOnlyFile(server.aof_filename) != C_OK) {
            addReply(c,shared.err);
            return;
        }
        server.dirty = 0; /* Prevent AOF / replication */
        serverLog(LL_WARNING,"Append Only File loaded by DEBUG LOADAOF");

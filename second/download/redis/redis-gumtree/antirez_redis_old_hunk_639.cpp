        serverLog(LL_WARNING,"DB reloaded by DEBUG RELOAD");
        addReply(c,shared.ok);
    } else if (!strcasecmp(c->argv[1]->ptr,"loadaof")) {
        emptyDb(-1,EMPTYDB_NO_FLAGS,NULL);
        if (loadAppendOnlyFile(server.aof_filename) != C_OK) {
            addReply(c,shared.err);

void scriptCommand(redisClient *c) {
    if (c->argc == 2 && !strcasecmp(c->argv[1]->ptr,"flush")) {
        scriptingReset();
        addReply(c,shared.ok);
        server.dirty++; /* Replicating this command is a good idea. */
    } else if (c->argc >= 2 && !strcasecmp(c->argv[1]->ptr,"exists")) {
        int j;

        addReplyMultiBulkLen(c, c->argc-2);
        for (j = 2; j < c->argc; j++) {
            if (dictFind(server.lua_scripts,c->argv[j]->ptr))
                addReply(c,shared.cone);
            else
                addReply(c,shared.czero);
        }
    } else if (c->argc == 3 && !strcasecmp(c->argv[1]->ptr,"load")) {
        char funcname[43];
        sds sha;

        funcname[0] = 'f';
        funcname[1] = '_';
        hashScript(funcname+2,c->argv[2]->ptr,sdslen(c->argv[2]->ptr));
        sha = sdsnewlen(funcname+2,40);
        if (dictFind(server.lua_scripts,sha) == NULL) {
            if (luaCreateFunction(c,server.lua,funcname,c->argv[2])
                    == REDIS_ERR) {
                sdsfree(sha);
                return;
            }
        }
        addReplyBulkCBuffer(c,funcname+2,40);
        sdsfree(sha);
    } else if (c->argc == 2 && !strcasecmp(c->argv[1]->ptr,"kill")) {
        if (server.lua_caller == NULL) {
            addReplyError(c,"No scripts in execution right now.");
        } else if (server.lua_write_dirty) {
            addReplyError(c, "Sorry the script already executed write commands against the dataset. You can either wait the script termination or kill the server in an hard way using the SHUTDOWN NOSAVE command.");
        } else {
            server.lua_kill = 1;
            addReply(c,shared.ok);
        }
    } else {
        addReplyError(c, "Unknown SCRIPT subcommand or wrong # of args.");
    }
}
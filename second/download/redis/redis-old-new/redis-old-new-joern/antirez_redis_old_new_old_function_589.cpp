void scriptCommand(client *c) {
    if (c->argc == 2 && !strcasecmp(c->argv[1]->ptr,"flush")) {
        scriptingReset();
        addReply(c,shared.ok);
        replicationScriptCacheFlush();
        server.dirty++; /* Propagating this command is a good idea. */
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
        sha1hex(funcname+2,c->argv[2]->ptr,sdslen(c->argv[2]->ptr));
        sha = sdsnewlen(funcname+2,40);
        if (dictFind(server.lua_scripts,sha) == NULL) {
            if (luaCreateFunction(c,server.lua,funcname,c->argv[2])
                    == C_ERR) {
                sdsfree(sha);
                return;
            }
        }
        addReplyBulkCBuffer(c,funcname+2,40);
        sdsfree(sha);
        forceCommandPropagation(c,PROPAGATE_REPL|PROPAGATE_AOF);
    } else if (c->argc == 2 && !strcasecmp(c->argv[1]->ptr,"kill")) {
        if (server.lua_caller == NULL) {
            addReplySds(c,sdsnew("-NOTBUSY No scripts in execution right now.\r\n"));
        } else if (server.lua_write_dirty) {
            addReplySds(c,sdsnew("-UNKILLABLE Sorry the script already executed write commands against the dataset. You can either wait the script termination or kill the server in a hard way using the SHUTDOWN NOSAVE command.\r\n"));
        } else {
            server.lua_kill = 1;
            addReply(c,shared.ok);
        }
    } else if (c->argc == 3 && !strcasecmp(c->argv[1]->ptr,"debug")) {
        if (clientHasPendingReplies(c)) {
            addReplyError(c,"SCRIPT DEBUG must be called outside a pipeline");
            return;
        }
        if (!strcasecmp(c->argv[2]->ptr,"no")) {
            ldbDisable(c);
            addReply(c,shared.ok);
        } else if (!strcasecmp(c->argv[2]->ptr,"yes")) {
            ldbEnable(c);
            addReply(c,shared.ok);
        } else if (!strcasecmp(c->argv[2]->ptr,"sync")) {
            ldbEnable(c);
            addReply(c,shared.ok);
            c->flags |= CLIENT_LUA_DEBUG_SYNC;
        } else {
            addReplyError(c,"Use SCRIPT DEBUG yes/async/no");
        }
    } else {
        addReplyError(c, "Unknown SCRIPT subcommand or wrong # of args.");
    }
}
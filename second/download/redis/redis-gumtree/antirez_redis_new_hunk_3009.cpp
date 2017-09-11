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
        sdsfree(sha);
        addReply(c,shared.ok);
    } else {
        addReplyError(c, "Unknown SCRIPT subcommand or wrong # of args.");

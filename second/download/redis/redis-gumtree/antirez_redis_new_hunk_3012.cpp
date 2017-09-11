            else
                addReply(c,shared.czero);
        }
    } else if (c->argc == 3 && !strcasecmp(c->argv[1]->ptr,"load")) {
        /* We obtain the script SHA1, then check if this function is already
         * defined into the Lua state */
        char funcname[43];

        funcname[0] = 'f';
        funcname[1] = '_';
        hashScript(funcname+2,c->argv[2]->ptr,sdslen(c->argv[2]->ptr));
        if (luaCreateFunction(c,server.lua,funcname,c->argv[2]) == REDIS_ERR)
            return;
        addReply(c,shared.ok);
    } else {
        addReplyError(c, "Unknown SCRIPT subcommand or wrong # of args.");
    }

            lua_pop(lua,1); /* remove the nil from the stack */
            return;
        }
        funcdef = sdsempty();

        lua_pop(lua,1); /* remove the nil from the stack */
        funcdef = sdscat(funcdef,"function ");
        funcdef = sdscatlen(funcdef,funcname,42);
        funcdef = sdscatlen(funcdef," ()\n",4);
        funcdef = sdscatlen(funcdef,c->argv[1]->ptr,sdslen(c->argv[1]->ptr));
        funcdef = sdscatlen(funcdef,"\nend\n",5);
        /* printf("Defining:\n%s\n",funcdef); */

        if (luaL_loadbuffer(lua,funcdef,sdslen(funcdef),"func definition")) {
            addReplyErrorFormat(c,"Error compiling script (new function): %s\n",
                lua_tostring(lua,-1));
            lua_pop(lua,1);
            sdsfree(funcdef);
            return;
        }
        sdsfree(funcdef);
        if (lua_pcall(lua,0,0,0)) {
            addReplyErrorFormat(c,"Error running script (new function): %s\n",
                lua_tostring(lua,-1));
            lua_pop(lua,1);
            return;
        }
        lua_getglobal(lua, funcname);

        /* We also save a SHA1 -> Original script map in a dictionary
         * so that we can replicate / write in the AOF all the
         * EVALSHA commands as EVAL using the original script. */
        {
            int retval = dictAdd(server.lua_scripts,
                                 sdsnewlen(funcname+2,40),c->argv[1]);
            redisAssertWithInfo(c,NULL,retval == DICT_OK);
            incrRefCount(c->argv[1]);
        }
    }

    /* Populate the argv and keys table accordingly to the arguments that

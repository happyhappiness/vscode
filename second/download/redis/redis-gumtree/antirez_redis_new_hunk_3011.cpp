            lua_pop(lua,1); /* remove the nil from the stack */
            return;
        }
        if (luaCreateFunction(c,lua,funcname,c->argv[1]) == REDIS_ERR) return;
        /* Now the following is guaranteed to return non nil */
        lua_getglobal(lua, funcname);
        redisAssert(!lua_isnil(lua,1));
    }

    /* Populate the argv and keys table accordingly to the arguments that

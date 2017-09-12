int luaCreateFunction(redisClient *c, lua_State *lua, char *funcname, robj *body) {
    sds funcdef = sdsempty();

    lua_pop(lua,1); /* remove the nil from the stack */
    funcdef = sdscat(funcdef,"function ");
    funcdef = sdscatlen(funcdef,funcname,42);
    funcdef = sdscatlen(funcdef," ()\n",4);
    funcdef = sdscatlen(funcdef,body->ptr,sdslen(body->ptr));
    funcdef = sdscatlen(funcdef,"\nend\n",5);

    if (luaL_loadbuffer(lua,funcdef,sdslen(funcdef),"func definition")) {
        addReplyErrorFormat(c,"Error compiling script (new function): %s\n",
            lua_tostring(lua,-1));
        lua_pop(lua,1);
        sdsfree(funcdef);
        return REDIS_ERR;
    }
    sdsfree(funcdef);
    if (lua_pcall(lua,0,0,0)) {
        addReplyErrorFormat(c,"Error running script (new function): %s\n",
            lua_tostring(lua,-1));
        lua_pop(lua,1);
        return REDIS_ERR;
    }

    /* We also save a SHA1 -> Original script map in a dictionary
     * so that we can replicate / write in the AOF all the
     * EVALSHA commands as EVAL using the original script. */
    {
        int retval = dictAdd(server.lua_scripts,
                             sdsnewlen(funcname+2,40),body);
        redisAssertWithInfo(c,NULL,retval == DICT_OK);
        incrRefCount(body);
    }
    return REDIS_OK;
}
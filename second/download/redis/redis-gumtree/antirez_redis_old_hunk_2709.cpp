    funcdef = sdscatlen(funcdef,body->ptr,sdslen(body->ptr));
    funcdef = sdscatlen(funcdef," end",4);

    if (luaL_loadbuffer(lua,funcdef,sdslen(funcdef),"func definition")) {
        addReplyErrorFormat(c,"Error compiling script (new function): %s\n",
            lua_tostring(lua,-1));
        lua_pop(lua,1);

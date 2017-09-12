int luaRedisCommand(lua_State *lua) {
    int j, argc = lua_gettop(lua);
    struct redisCommand *cmd;
    robj **argv;
    redisClient *c = server.lua_client;
    sds reply;

    /* Build the arguments vector */
    argv = zmalloc(sizeof(robj*)*argc);
    for (j = 0; j < argc; j++)
        argv[j] = createStringObject((char*)lua_tostring(lua,j+1),
                                     lua_strlen(lua,j+1));

    /* Command lookup */
    cmd = lookupCommand(argv[0]->ptr);
    if (!cmd) {
        for (j = 0; j < argc; j++) decrRefCount(argv[j]);
        zfree(argv);
        lua_newtable(lua);
        lua_pushstring(lua,"err");
        lua_pushstring(lua,"Unknown Redis command called from Lua script");
        lua_settable(lua,-3);
        return 1;
    }

    /* Run the command in the context of a fake client */
    c->argv = argv;
    c->argc = argc;
    cmd->proc(c);

    /* Convert the result of the Redis command into a suitable Lua type.
     * The first thing we need is to create a single string from the client
     * output buffers. */
    reply = sdsempty();
    if (c->bufpos) {
        reply = sdscatlen(reply,c->buf,c->bufpos);
        c->bufpos = 0;
    }
    while(listLength(c->reply)) {
        robj *o = listNodeValue(listFirst(c->reply));

        sdscatlen(reply,o->ptr,sdslen(o->ptr));
        listDelNode(c->reply,listFirst(c->reply));
    }
    redisProtocolToLuaType(lua,reply);
    sdsfree(reply);

    /* Clean up. Command code may have changed argv/argc so we use the
     * argv/argc of the client instead of the local variables. */
    for (j = 0; j < c->argc; j++)
        decrRefCount(c->argv[j]);
    zfree(c->argv);

    return 1;
}
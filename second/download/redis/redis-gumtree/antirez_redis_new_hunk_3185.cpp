    lua_pop(lua,1);
}

/* Set an array of Redis String Objects as a Lua array (table) stored into a
 * global variable. */
void luaSetGlobalArray(lua_State *lua, char *var, robj **elev, int elec) {
    int j;

    lua_newtable(lua);
    for (j = 0; j < elec; j++) {
        lua_pushlstring(lua,(char*)elev[j]->ptr,sdslen(elev[j]->ptr));
        lua_rawseti(lua,-2,j+1);
    }
    lua_setglobal(lua,var);
}

void evalCommand(redisClient *c) {
    lua_State *lua = server.lua;
    char funcname[43];
    long long numkeys;

    /* Get the number of arguments that are keys */
    if (getLongLongFromObjectOrReply(c,c->argv[2],&numkeys,NULL) != REDIS_OK)
        return;
    if (numkeys > (c->argc - 3)) {
        addReplyError(c,"Number of keys can't be greater than number of args");
        return;
    }

    /* We obtain the script SHA1, then check if this function is already
     * defined into the Lua state */

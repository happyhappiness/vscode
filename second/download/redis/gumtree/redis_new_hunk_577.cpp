        p = redisProtocolToLuaType(lua,p);
        lua_settable(lua,-3);
    }
    return p;
}

/* This function is used in order to push an error on the Lua stack in the
 * format used by redis.pcall to return errors, which is a lua table
 * with a single "err" field set to the error string. Note that this
 * table is never a valid reply by proper commands, since the returned
 * tables are otherwise always indexed by integers, never by strings. */
void luaPushError(lua_State *lua, char *error) {
    lua_Debug dbg;

    /* If debugging is active and in step mode, log errors resulting from
     * Redis commands. */
    if (ldb.active && ldb.step) {
        ldbLog(sdscatprintf(sdsempty(),"<error> %s",error));
    }

    lua_newtable(lua);
    lua_pushstring(lua,"err");

    /* Attempt to figure out where this function was called, if possible */
    if(lua_getstack(lua, 1, &dbg) && lua_getinfo(lua, "nSl", &dbg)) {
        sds msg = sdscatprintf(sdsempty(), "%s: %d: %s",

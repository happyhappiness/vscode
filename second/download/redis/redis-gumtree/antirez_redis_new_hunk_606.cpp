void luaPushError(lua_State *lua, char *error) {
    lua_Debug dbg;

    /* If debugging is active and in step mode, log errors resulting from
     * Redis commands. */
    if (ldb.active && ldb.step) {
        ldbLog(sdscatprintf(sdsempty(),"<error> %s",error));
    }

    lua_newtable(lua);
    lua_pushstring(lua,"err");


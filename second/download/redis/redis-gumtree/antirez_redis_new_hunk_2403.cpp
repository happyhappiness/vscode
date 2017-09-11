}

void luaPushError(lua_State *lua, char *error) {
    lua_Debug dbg;

    lua_newtable(lua);
    lua_pushstring(lua,"err");

    /* Attempt to figure out where this function was called, if possible */
    if(lua_getstack(lua, 1, &dbg) && lua_getinfo(lua, "nSl", &dbg)) {
        sds msg = sdscatprintf(sdsempty(), "%s: %d: %s",
            dbg.source, dbg.currentline, error);
        lua_pushstring(lua, msg);
        sdsfree(msg);
    } else {
        lua_pushstring(lua, error);
    }
    lua_settable(lua,-3);
}


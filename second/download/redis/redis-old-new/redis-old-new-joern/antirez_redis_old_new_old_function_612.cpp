void luaLdbLineHook(lua_State *lua, lua_Debug *ar) {
    lua_getstack(lua,0,ar);
    lua_getinfo(lua,"Sl",ar);
    if(strstr(ar->short_src,"user_script") == NULL) return;

    if (ldb.step) {
        ldb.step = 0;
        ldbLog(sdscatprintf(sdsempty(),"%d: %s", (int)ar->currentline,
            ldbGetSourceLine(ar->currentline-1)));
        ldbSendLogs();
        ldbRepl();
    }
}
void luaLdbLineHook(lua_State *lua, lua_Debug *ar) {
    lua_getstack(lua,0,ar);
    lua_getinfo(lua,"Sl",ar);
    if(strstr(ar->short_src,"user_script") == NULL) return;

    if (ldb.step || ldbIsBreakpoint(ar->currentline)) {
        ldb.currentline = ar->currentline;
        ldb.step = 0;
        int mark = ldbIsBreakpoint(ldb.currentline) ? '#' : '*';
        ldbLog(sdscatprintf(sdsempty(),"%d%c %s", (int)ar->currentline,
            mark, ldbGetSourceLine(ar->currentline)));
        ldbSendLogs();
        ldbRepl(lua);
    }
}
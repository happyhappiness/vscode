    lua_getinfo(lua,"Sl",ar);
    if(strstr(ar->short_src,"user_script") == NULL) return;

    int bp = ldbIsBreakpoint(ar->currentline) || ldb.luabp;
    if (ldb.step || bp) {
        char *reason = "step over";
        if (bp) reason = ldb.luabp ? "redis.breakpoint() called" :
                                     "break point";
        ldb.currentline = ar->currentline;
        ldb.step = 0;
        ldb.luabp = 0;
        ldbLog(sdscatprintf(sdsempty(),
            "* Stopped at %d, stop reason = %s",
            ldb.currentline, reason));

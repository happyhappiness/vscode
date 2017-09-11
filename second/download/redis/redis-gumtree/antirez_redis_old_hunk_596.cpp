    lua_getinfo(lua,"Sl",ar);
    if(strstr(ar->short_src,"user_script") == NULL) return;

    int bp = ldbIsBreakpoint(ar->currentline);
    if (ldb.step || bp) {
        char *reason = bp ? "break point" : "step over";
        ldb.currentline = ar->currentline;
        ldb.step = 0;
        ldbLog(sdscatprintf(sdsempty(),
            "* Stopped at %d, stop reason = %s",
            ldb.currentline, reason));


    for (j = 1; j <= ldb.lines; j++) {
        if (around != 0 && abs(around-j) > context) continue;
        char *line = ldbGetSourceLine(j);
        int mark;
        if (ldb.currentline == j)
            mark = '*';
        else
            mark = ldbIsBreakpoint(j) ? '#' : ':';
        sds thisline = sdscatprintf(sdsempty(),"%d%c %s", j, mark, line);
        ldbLog(thisline);
    }
}

/* Produce a debugger log entry representing the value of the Lua object
 * currently on the top of the stack. */
void ldbLogStackValue(lua_State *lua) {
    int t = lua_type(lua,-1);
    sds s = sdsnew("<value> ");

    switch(t) {
    case LUA_TSTRING:

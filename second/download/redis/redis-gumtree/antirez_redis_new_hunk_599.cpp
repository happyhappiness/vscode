
    for (j = 1; j <= ldb.lines; j++) {
        if (around != 0 && abs(around-j) > context) continue;
        ldbLogSourceLine(j);
    }
}

/* Produce a debugger log entry representing the value of the Lua object
 * currently on the top of the stack. As a side effect the element is
 * popped. */
void ldbLogStackValue(lua_State *lua, char *prefix) {
    int t = lua_type(lua,-1);
    sds s = sdsnew(prefix);

    switch(t) {
    case LUA_TSTRING:

    lua_pop(lua,2);             /* Discard the result and clean the stack. */
}

/* Implements "trace" command of the Lua debugger. It just prints a backtrace
 * querying Lua starting from the current callframe back to the outer one. */
void ldbTrace(lua_State *lua) {
    lua_Debug ar;
    int level = 0;

    while(lua_getstack(lua,level,&ar)) {
        lua_getinfo(lua,"Snl",&ar);
        if(strstr(ar.short_src,"user_script") == NULL) continue;
        ldbLog(sdscatprintf(sdsempty(),"%s %s:",
            (level == 0) ? "In" : "From",
            ar.name ? ar.name : "top level"));
        ldbLogSourceLine(ar.currentline);
        level++;
    }
    if (level == 0) {
        ldbLog(sdsnew("<error> Can't retrieve Lua stack."));
    }
}

/* Read debugging commands from client. */
void ldbRepl(lua_State *lua) {
    sds *argv;

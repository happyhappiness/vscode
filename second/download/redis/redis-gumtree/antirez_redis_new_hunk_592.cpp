    return 1;
}

/* redis.debug()
 *
 * Log a string message into the output console.
 * Can take multiple arguments that will be separated by commas.
 * Nothing is returned to the caller. */
int luaRedisDebugCommand(lua_State *lua) {
    if (!ldb.active) return 0;
    int argc = lua_gettop(lua);
    sds log = sdscatprintf(sdsempty(),"<debug> line %d: ", ldb.currentline);
    while(argc--) {
        log = ldbCatStackValue(log,lua,-1 - argc);
        if (argc != 0) log = sdscatlen(log,", ",2);
    }
    ldbLog(log);
    return 0;
}

/* redis.set_repl()
 *
 * Set the propagation of write commands executed in the context of the

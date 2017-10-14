static int loadjitmodule(lua_State *L, apr_pool_t *lifecycle_pool) {
    lua_getglobal(L, "require");
    lua_pushliteral(L, "jit.");
    lua_pushvalue(L, -3);
    lua_concat(L, 2);
    if (lua_pcall(L, 1, 1, 0)) {
        const char *msg = lua_tostring(L, -1);
        ap_log_perror(APLOG_MARK, APLOG_DEBUG, 0, lifecycle_pool,
                      "Failed to init LuaJIT: %s", msg);
        return 1;
    }
    lua_getfield(L, -1, "start");
    lua_remove(L, -2);  /* drop module table */
    return 0;
}
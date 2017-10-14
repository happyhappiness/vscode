static apr_status_t vm_construct(void **vm, void *params, apr_pool_t *lifecycle_pool)
{
    lua_State* L;

    ap_lua_vm_spec *spec = params;

    L = luaL_newstate();
#ifdef AP_ENABLE_LUAJIT
    luaopen_jit(L);
#endif
    luaL_openlibs(L);
    if (spec->package_paths) {
        munge_path(L, 
                   "path", "?.lua", "./?.lua", 
                   lifecycle_pool,
                   spec->package_paths, 
                   spec->file);
    }
    if (spec->package_cpaths) {
        munge_path(L, "cpath", "?.so", "./?.so", lifecycle_pool,
            spec->package_cpaths, spec->file);
    }

    if (spec->cb) {
        spec->cb(L, lifecycle_pool, spec->cb_arg);
    }


    if (spec->bytecode && spec->bytecode_len > 0) {
        luaL_loadbuffer(L, spec->bytecode, spec->bytecode_len, spec->file);
        lua_pcall(L, 0, LUA_MULTRET, 0);
    }
    else {
        int rc;
        ap_log_perror(APLOG_MARK, APLOG_DEBUG, 0, lifecycle_pool, APLOGNO(01481)
            "loading lua file %s", spec->file);
        rc = luaL_loadfile(L, spec->file);
        if (rc != 0) {
            char *err;
            switch (rc) {
                case LUA_ERRSYNTAX:
                    err = "syntax error";
                    break;
                case LUA_ERRMEM:
                    err = "memory allocation error";
                    break;
                case LUA_ERRFILE:
                    err = "error opening or reading file";
                    break;
                default:
                    err = "unknown error";
                    break;
            }
            ap_log_perror(APLOG_MARK, APLOG_ERR, 0, lifecycle_pool, APLOGNO(01482)
                "Loading lua file %s: %s",
                spec->file, err);
            return APR_EBADF;
        }
        lua_pcall(L, 0, LUA_MULTRET, 0);
    }

#ifdef AP_ENABLE_LUAJIT
    loadjitmodule(L, lifecycle_pool);
#endif
    lua_pushlightuserdata(L, lifecycle_pool);
    lua_setfield(L, LUA_REGISTRYINDEX, "Apache2.Wombat.pool");
    *vm = L;

    return APR_SUCCESS;
}
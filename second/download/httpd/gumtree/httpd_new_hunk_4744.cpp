    else {
        int rc;
        ap_log_perror(APLOG_MARK, APLOG_DEBUG, 0, lifecycle_pool, APLOGNO(01481)
            "loading lua file %s", spec->file);
        rc = luaL_loadfile(L, spec->file);
        if (rc != 0) {
            ap_log_perror(APLOG_MARK, APLOG_ERR, 0, lifecycle_pool, APLOGNO(01482)
                          "Error loading %s: %s", spec->file,
                          rc == LUA_ERRMEM ? "memory allocation error"
                                           : lua_tostring(L, 0));
            return APR_EBADF;
        }
        lua_pcall(L, 0, LUA_MULTRET, 0);
    }

#ifdef AP_ENABLE_LUAJIT

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

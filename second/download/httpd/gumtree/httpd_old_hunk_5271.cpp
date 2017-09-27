            ap_log_perror(APLOG_MARK, APLOG_ERR, 0, lifecycle_pool, APLOGNO(01482)
                          "Error loading %s: %s", spec->file,
                          rc == LUA_ERRMEM ? "memory allocation error"
                                           : lua_tostring(L, 0));
            return APR_EBADF;
        }
        lua_pcall(L, 0, LUA_MULTRET, 0);
    }

#ifdef AP_ENABLE_LUAJIT
    loadjitmodule(L, lifecycle_pool);
#endif
    lua_pushlightuserdata(L, lifecycle_pool);

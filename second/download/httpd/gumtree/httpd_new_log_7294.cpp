ap_log_perror(APLOG_MARK, APLOG_ERR, 0, lifecycle_pool, APLOGNO(02333)
                          "Error loading %s: %s", spec->file,
                          rc == LUA_ERRMEM ? "memory allocation error"
                                           : lua_tostring(L, 0));
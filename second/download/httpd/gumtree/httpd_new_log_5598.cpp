ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(02663)
                              "lua: Error while executing filter: %s",
                              lua_tostring(L, -1));
ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, r,
                              "%d:  '%s'", i, lua_tostring(L, i));
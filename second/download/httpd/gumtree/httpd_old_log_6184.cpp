ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, r,
                              "%d:  %g", i, lua_tonumber(L, i));
ap_log_perror(APLOG_MARK, level, 0, r,
                              "%d:  %g", i, lua_tonumber(L, i));
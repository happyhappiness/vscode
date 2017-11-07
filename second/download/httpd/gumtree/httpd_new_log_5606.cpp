ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, r, APLOGNO(03006)
                              "%d:  %s", i,
                              lua_toboolean(L, i) ? "true" : "false");
ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, r,
                              "%d:  %s", i, lua_toboolean(L,
                                                          i) ? "true" :
                              "false");
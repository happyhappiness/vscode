ap_log_perror(APLOG_MARK, level, 0, r,
                              "%d:  %s", i, lua_toboolean(L,
                                                          i) ? "true" :
                              "false");
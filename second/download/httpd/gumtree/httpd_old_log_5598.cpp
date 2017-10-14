ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                                    "lua: Error while executing filter: %s",
                        lua_tostring(L, -1));
ap_log_perror(APLOG_MARK, APLOG_ERR, 0, lifecycle_pool, APLOGNO(02613)
                          "Error loading %s: %s", spec->file,
                            lua_tostring(L, -1));
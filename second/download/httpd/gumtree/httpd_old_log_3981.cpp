ap_log_perror(APLOG_MARK, APLOG_WARNING, 0, r->pool, "Lua error: %s",
                  lua_response);
            return HTTP_INTERNAL_SERVER_ERROR;
        }
        ap_log_rerror(APLOG_MARK, APLOG_TRACE3, 0, r, APLOGNO(01474) "got a vm!");
        lua_getglobal(L, "handle");
        if (!lua_isfunction(L, -1)) {
            ap_log_rerror(APLOG_MARK, APLOG_CRIT, 0, r, APLOGNO(01475)
                          "lua: Unable to find entry function '%s' in %s (not a valid function)",
                          "handle",
                          spec->file);
            ap_lua_release_state(L, spec, r);
            return HTTP_INTERNAL_SERVER_ERROR;
        }
        ap_lua_run_lua_request(L, r);

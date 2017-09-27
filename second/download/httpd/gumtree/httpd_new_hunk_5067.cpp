                ap_lua_release_state(L, spec, r);
                return HTTP_INTERNAL_SERVER_ERROR;
            }
            rc = DECLINED;
            if (lua_isnumber(L, -1)) {
                rc = lua_tointeger(L, -1);
                ap_log_rerror(APLOG_MARK, APLOG_TRACE4, 0, r, "Lua hook %s:%s for phase %s returned %d", 
                              hook_spec->file_name, hook_spec->function_name, name, rc);
            }
            else { 
                ap_log_rerror(APLOG_MARK, APLOG_CRIT, 0, r, "Lua hook %s:%s for phase %s did not return a numeric value", 
                              hook_spec->file_name, hook_spec->function_name, name);
                return HTTP_INTERNAL_SERVER_ERROR;
            }
            if (rc != DECLINED) {
                ap_lua_release_state(L, spec, r);
                return rc;
            }
            ap_lua_release_state(L, spec, r);

                ap_lua_release_state(L, spec, r);
                return HTTP_INTERNAL_SERVER_ERROR;
            }
            rc = DECLINED;
            if (lua_isnumber(L, -1)) {
                rc = lua_tointeger(L, -1);
            }
            if (rc != DECLINED) {
                ap_lua_release_state(L, spec, r);
                return rc;
            }
            ap_lua_release_state(L, spec, r);

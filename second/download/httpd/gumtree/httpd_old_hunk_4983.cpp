                lua_setglobal(L, "r");
                lua_settop(L, t);
            }

            if (lua_pcall(L, 1, 1, 0)) {
                report_lua_error(L, r);
                return HTTP_INTERNAL_SERVER_ERROR;
            }
            rc = DECLINED;
            if (lua_isnumber(L, -1)) {
                rc = lua_tointeger(L, -1);
            }
            if (rc != DECLINED) {
                return rc;
            }
        }
    }
    return DECLINED;
}

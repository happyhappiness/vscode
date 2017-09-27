    int top = lua_gettop(L);
    ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, r, APLOGNO(01484) "Lua Stack Dump: [%s]", msg);
    for (i = 1; i <= top; i++) {
        int t = lua_type(L, i);
        switch (t) {
        case LUA_TSTRING:{
                ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, r, APLOGNO(03001)
                              "%d:  '%s'", i, lua_tostring(L, i));
                break;
            }
        case LUA_TUSERDATA:{
                ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, r, APLOGNO(03002)
                              "%d:  userdata", i);
                break;
            }
        case LUA_TLIGHTUSERDATA:{
                ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, r, APLOGNO(03003)
                              "%d:  lightuserdata", i);
                break;
            }
        case LUA_TNIL:{
                ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, r, APLOGNO(03004)
                              "%d:  NIL", i);
                break;
            }
        case LUA_TNONE:{
                ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, r, APLOGNO(03005)
                              "%d:  None", i);
                break;
            }
        case LUA_TBOOLEAN:{
                ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, r, APLOGNO(03006)
                              "%d:  %s", i,
                              lua_toboolean(L, i) ? "true" : "false");
                break;
            }
        case LUA_TNUMBER:{
                ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, r, APLOGNO(03007)
                              "%d:  %g", i, lua_tonumber(L, i));
                break;
            }
        case LUA_TTABLE:{
                ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, r, APLOGNO(03008)
                              "%d:  <table>", i);
                break;
            }
        case LUA_TFUNCTION:{
                ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, r, APLOGNO(03009)
                              "%d:  <function>", i);
                break;
            }
        default:{
                ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, r, APLOGNO(03010)
                              "%d:  unknown: -[%s]-", i, lua_typename(L, i));
                break;
            }
        }
    }
}

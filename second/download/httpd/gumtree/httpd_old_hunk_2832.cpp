
void ap_lua_rstack_dump(lua_State *L, request_rec *r, const char *msg)
{
    int i;
    int top = lua_gettop(L);

    ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, r, "Lua Stack Dump: [%s]", msg);

    for (i = 1; i <= top; i++) {
        int t = lua_type(L, i);
        switch (t) {
        case LUA_TSTRING:{
                ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, r,

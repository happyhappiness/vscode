static int req_write(lua_State *L)
{
    request_rec *r = ap_lua_check_request_rec(L, 1);
    size_t n;
    const char *buf = luaL_checklstring(L, 2, &n);

    ap_rwrite((void *) buf, n, r);
    return 0;
}
static int lua_set_cookie(lua_State *L) 
{
    const char *key, *value, *out, *strexpires;
    int secure, expires;
    char cdate[APR_RFC822_DATE_LEN+1];
    apr_status_t rv;
    request_rec *r = ap_lua_check_request_rec(L, 1);
    key = luaL_checkstring(L, 2);
    value = luaL_checkstring(L, 3);
    secure = 0;
    if (lua_isboolean(L, 4)) {
        secure = lua_toboolean(L, 4);
    }
    expires = luaL_optinteger(L, 5, 0);
    strexpires = "";
    if (expires > 0) {
        rv = apr_rfc822_date(cdate, apr_time_from_sec(expires));
        if (rv == APR_SUCCESS) {
            strexpires = apr_psprintf(r->pool, "Expires=%s", cdate);
        }
    }
    out = apr_psprintf(r->pool, "%s=%s; %s %s", key, value, secure ? "Secure;" : "", expires ? strexpires : "");
    apr_table_set(r->headers_out, "Set-Cookie", out);
    return 0;
}
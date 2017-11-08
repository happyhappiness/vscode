static void report_lua_error(lua_State *L, request_rec *r)
{
    const char *lua_response;
    r->status = HTTP_INTERNAL_SERVER_ERROR;
    r->content_type = "text/html";
    ap_rputs("<b>Error!</b>\n", r);
    ap_rputs("<p>", r);
    lua_response = lua_tostring(L, -1);
    ap_rputs(lua_response, r);
    ap_rputs("</p>\n", r);

    ap_log_perror(APLOG_MARK, APLOG_WARNING, 0, r->pool, APLOGNO(01471) "Lua error: %s",
                  lua_response);
}
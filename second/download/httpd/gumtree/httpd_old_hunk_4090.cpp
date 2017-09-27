static int lua_auth_checker_harness_last(request_rec *r)
{
    return lua_request_rec_hook_harness(r, "auth_checker", AP_LUA_HOOK_LAST);
}
static void lua_insert_filter_harness(request_rec *r)
{
    /* ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r, "LuaHookInsertFilter not yet implemented"); */
}

static int lua_log_transaction_harness(request_rec *r)
{
    return lua_request_rec_hook_harness(r, "log_transaction", APR_HOOK_FIRST);
}

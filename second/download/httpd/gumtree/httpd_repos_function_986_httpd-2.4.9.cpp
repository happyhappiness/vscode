static int lua_check_user_id_harness_first(request_rec *r)
{
    return lua_request_rec_hook_harness(r, "check_user_id", AP_LUA_HOOK_FIRST);
}
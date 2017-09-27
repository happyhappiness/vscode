    spec->function_name = apr_pstrdup(cmd->pool, function);
    spec->scope = cfg->vm_scope;

    *(ap_lua_mapped_handler_spec **) apr_array_push(hook_specs) = spec;
    return NULL;
}

static int lua_check_user_id_harness_first(request_rec *r)
{
    return lua_request_rec_hook_harness(r, "check_user_id", AP_LUA_HOOK_FIRST);
}
static int lua_check_user_id_harness(request_rec *r)
{

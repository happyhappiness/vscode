static void lua_register_hooks(apr_pool_t *p)
{
    /* ap_register_output_filter("luahood", luahood, NULL, AP_FTYPE_RESOURCE); */
    ap_hook_handler(lua_handler, NULL, NULL, APR_HOOK_MIDDLE);
    ap_hook_create_request(create_request_config, NULL, NULL,
                           APR_HOOK_MIDDLE);

    /* http_request.h hooks */
    ap_hook_translate_name(lua_translate_name_harness, NULL, NULL,
                           APR_HOOK_MIDDLE);
    ap_hook_fixups(lua_fixup_harness, NULL, NULL, APR_HOOK_MIDDLE);
    ap_hook_map_to_storage(lua_map_to_storage_harness, NULL, NULL,
                           APR_HOOK_MIDDLE);
    ap_hook_check_user_id(lua_check_user_id_harness, NULL, NULL,
                          APR_HOOK_MIDDLE);
    ap_hook_type_checker(lua_type_checker_harness, NULL, NULL,
                         APR_HOOK_MIDDLE);
    ap_hook_access_checker(lua_access_checker_harness, NULL, NULL,
                           APR_HOOK_MIDDLE);
    ap_hook_auth_checker(lua_auth_checker_harness, NULL, NULL,
                         APR_HOOK_MIDDLE);
    ap_hook_insert_filter(lua_insert_filter_harness, NULL, NULL,
                          APR_HOOK_MIDDLE);
    ap_hook_quick_handler(lua_quick_harness, NULL, NULL, APR_HOOK_FIRST);

    /* ap_hook_translate_name(lua_alias_munger, NULL, NULL, APR_HOOK_MIDDLE); */
    ap_hook_translate_name(lua_alias_munger, NULL, NULL, APR_HOOK_MIDDLE);

    APR_OPTIONAL_HOOK(ap_lua, lua_open, lua_open_hook, NULL, NULL,
                      APR_HOOK_REALLY_FIRST);

    APR_OPTIONAL_HOOK(ap_lua, lua_request, lua_request_hook, NULL, NULL,
                      APR_HOOK_REALLY_FIRST);
}
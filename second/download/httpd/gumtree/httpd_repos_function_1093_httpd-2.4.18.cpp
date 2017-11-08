static int cfg_lua_map_handler(lua_State *L)
{
    ap_lua_dir_cfg *cfg = check_dir_config(L, 1);
    ap_lua_mapped_handler_spec *handler =
        apr_pcalloc(cfg->pool, sizeof(ap_lua_mapped_handler_spec));
    handler->uri_pattern = NULL;
    handler->function_name = NULL;

    luaL_checktype(L, 2, LUA_TTABLE);
    lua_getfield(L, 2, "file");
    if (lua_isstring(L, -1)) {
        const char *file = lua_tostring(L, -1);
        handler->file_name = apr_pstrdup(cfg->pool, file);
    }
    lua_pop(L, 1);

    lua_getfield(L, 2, "pattern");
    if (lua_isstring(L, -1)) {
        const char *pattern = lua_tostring(L, -1);

        ap_regex_t *uri_pattern = apr_palloc(cfg->pool, sizeof(ap_regex_t));
        if (ap_regcomp(uri_pattern, pattern, 0) != OK) {
            return luaL_error(L, "Unable to compile regular expression, '%s'",
                              pattern);
        }
        handler->uri_pattern = uri_pattern;
    }
    lua_pop(L, 1);

    lua_getfield(L, 2, "scope");
    if (lua_isstring(L, -1)) {
        const char *scope = lua_tostring(L, -1);
        handler->scope = apl_toscope(scope);
    }
    else {
        handler->scope = AP_LUA_SCOPE_ONCE;
    }
    lua_pop(L, 1);

    lua_getfield(L, 2, "func");
    if (lua_isstring(L, -1)) {
        const char *value = lua_tostring(L, -1);
        handler->function_name = apr_pstrdup(cfg->pool, value);
    }
    else {
        handler->function_name = "handle";
    }
    lua_pop(L, 1);


    *(const ap_lua_mapped_handler_spec **) apr_array_push(cfg->mapped_handlers) =
        handler;
    return 0;
}
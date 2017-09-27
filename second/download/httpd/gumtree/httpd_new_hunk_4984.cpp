    spec->function_name = apr_pstrdup(cmd->pool, function);
    spec->scope = cfg->vm_scope;

    *(ap_lua_mapped_handler_spec **) apr_array_push(hook_specs) = spec;
    return NULL;
}
static const char *register_mapped_file_function_hook(const char *pattern,
                                                     cmd_parms *cmd,
                                                     void *_cfg,
                                                     const char *file,
                                                     const char *function)
{
    ap_lua_mapped_handler_spec *spec;
    ap_lua_dir_cfg *cfg = (ap_lua_dir_cfg *) _cfg;
    ap_regex_t *regex = apr_pcalloc(cmd->pool, sizeof(ap_regex_t));
    if (ap_regcomp(regex, pattern,0)) {
        return "Invalid regex pattern!";
    }

    spec = apr_pcalloc(cmd->pool, sizeof(ap_lua_mapped_handler_spec));
    spec->file_name = apr_pstrdup(cmd->pool, file);
    spec->function_name = apr_pstrdup(cmd->pool, function);
    spec->scope = cfg->vm_scope;
    spec->uri_pattern = regex;

    *(ap_lua_mapped_handler_spec **) apr_array_push(cfg->mapped_handlers) = spec;
    return NULL;
}
static const char *register_filter_function_hook(const char *filter,
                                                     cmd_parms *cmd,
                                                     void *_cfg,
                                                     const char *file,
                                                     const char *function,
                                                     int direction)
{
    ap_lua_filter_handler_spec *spec;
    ap_lua_dir_cfg *cfg = (ap_lua_dir_cfg *) _cfg;
   
    spec = apr_pcalloc(cmd->pool, sizeof(ap_lua_filter_handler_spec));
    spec->file_name = apr_pstrdup(cmd->pool, file);
    spec->function_name = apr_pstrdup(cmd->pool, function);
    spec->filter_name = filter;

    *(ap_lua_filter_handler_spec **) apr_array_push(cfg->mapped_filters) = spec;
    /* TODO: Make it work on other types than just AP_FTYPE_RESOURCE? */
    if (direction == AP_LUA_FILTER_OUTPUT) {
        spec->direction = AP_LUA_FILTER_OUTPUT;
        ap_register_output_filter(filter, lua_output_filter_handle, NULL, AP_FTYPE_RESOURCE);
    }
    else {
        spec->direction = AP_LUA_FILTER_INPUT;
        ap_register_input_filter(filter, lua_input_filter_handle, NULL, AP_FTYPE_RESOURCE);
    }
    return NULL;
}
static int lua_check_user_id_harness_first(request_rec *r)
{
    return lua_request_rec_hook_harness(r, "check_user_id", AP_LUA_HOOK_FIRST);
}
static int lua_check_user_id_harness(request_rec *r)
{

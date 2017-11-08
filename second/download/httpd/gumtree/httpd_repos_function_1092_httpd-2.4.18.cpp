apr_status_t ap_lua_map_handler(ap_lua_dir_cfg *cfg,
                                                 const char *file,
                                                 const char *function,
                                                 const char *pattern,
                                                 const char *scope)
{
    ap_regex_t *uri_pattern;
    apr_status_t rv;
    ap_lua_mapped_handler_spec *handler =
        apr_pcalloc(cfg->pool, sizeof(ap_lua_mapped_handler_spec));
    handler->uri_pattern = NULL;
    handler->function_name = NULL;

    uri_pattern = apr_palloc(cfg->pool, sizeof(ap_regex_t));
    if ((rv = ap_regcomp(uri_pattern, pattern, 0)) != APR_SUCCESS) {
        return rv;
    }
    handler->file_name = apr_pstrdup(cfg->pool, file);
    handler->uri_pattern = uri_pattern;
    handler->scope = apl_toscope(scope);

    handler->function_name = apr_pstrdup(cfg->pool, function);
    *(const ap_lua_mapped_handler_spec **) apr_array_push(cfg->mapped_handlers) =
        handler;
    return APR_SUCCESS;
}
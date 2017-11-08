static const char *register_named_file_function_hook(const char *name,
                                                     cmd_parms *cmd,
                                                     void *_cfg,
                                                     const char *file,
                                                     const char *function)
{
    ap_lua_mapped_handler_spec *spec;
    ap_lua_dir_cfg *cfg = (ap_lua_dir_cfg *) _cfg;

    apr_array_header_t *hook_specs =
        apr_hash_get(cfg->hooks, name, APR_HASH_KEY_STRING);
    if (!hook_specs) {
        hook_specs =
            apr_array_make(cmd->pool, 2, sizeof(ap_lua_mapped_handler_spec *));
        apr_hash_set(cfg->hooks, apr_pstrdup(cmd->pool, name),
                     APR_HASH_KEY_STRING, hook_specs);
    }

    spec = apr_pcalloc(cmd->pool, sizeof(ap_lua_mapped_handler_spec));
    spec->file_name = apr_pstrdup(cmd->pool, file);
    spec->function_name = apr_pstrdup(cmd->pool, function);
    spec->scope = cfg->vm_scope;
    spec->code_cache_style = APL_CODE_CACHE_STAT;
    /*
       int code_cache_style;
       char *function_name;
       char *file_name;
       int scope;
     */
    *(ap_lua_mapped_handler_spec **) apr_array_push(hook_specs) = spec;
    return NULL;
}
static const char *hack_section_handler(cmd_parms *cmd, void *_cfg,
                                        const char *arg)
{
    ap_lua_dir_cfg *cfg = (ap_lua_dir_cfg *) _cfg;
    ap_directive_t *directive = cmd->directive;
    hack_section_baton *baton = directive->data;

    apr_array_header_t *hook_specs =
        apr_hash_get(cfg->hooks, baton->name, APR_HASH_KEY_STRING);
    if (!hook_specs) {
        hook_specs =
            apr_array_make(cmd->pool, 2, sizeof(ap_lua_mapped_handler_spec *));
        apr_hash_set(cfg->hooks, apr_pstrdup(cmd->pool, baton->name),
                     APR_HASH_KEY_STRING, hook_specs);
    }

    baton->spec->scope = cfg->vm_scope;

    *(ap_lua_mapped_handler_spec **) apr_array_push(hook_specs) = baton->spec;

    return NULL;
}
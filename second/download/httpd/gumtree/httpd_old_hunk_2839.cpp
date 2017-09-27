            *current = apr_pcalloc(cmd->pool, sizeof(**current));
        }

        baton = apr_pcalloc(cmd->pool, sizeof(hack_section_baton));
        baton->name = name;
        baton->spec = spec;

        (*current)->filename = cmd->config_file->name;
        (*current)->line_num = cmd->config_file->line_number;
        (*current)->directive =
            apr_pstrdup(cmd->pool, "Lua_____ByteCodeHack");
        (*current)->args = NULL;
        (*current)->data = baton;
    }

    return NULL;
}

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

static int lua_check_user_id_harness(request_rec *r)
{
    return lua_request_rec_hook_harness(r, "check_user_id");
}

static int lua_translate_name_harness(request_rec *r)
{
    return lua_request_rec_hook_harness(r, "translate_name");
}

static int lua_fixup_harness(request_rec *r)
{
    return lua_request_rec_hook_harness(r, "fixups");
}

static int lua_map_to_storage_harness(request_rec *r)
{
    return lua_request_rec_hook_harness(r, "map_to_storage");
}

static int lua_type_checker_harness(request_rec *r)
{
    return lua_request_rec_hook_harness(r, "type_checker");
}

static int lua_access_checker_harness(request_rec *r)
{
    return lua_request_rec_hook_harness(r, "access_checker");
}

static int lua_auth_checker_harness(request_rec *r)
{
    return lua_request_rec_hook_harness(r, "auth_checker");
}

static void lua_insert_filter_harness(request_rec *r)
{
    /* ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r, "LuaHookInsertFilter not yet implemented"); */
}

static int lua_quick_harness(request_rec *r, int lookup)

static const char *register_named_block_function_hook(const char *name,
                                                      cmd_parms *cmd,
                                                      void *mconfig,
                                                      const char *line)
{
    const char *function = NULL;
    ap_lua_mapped_handler_spec *spec;
    int when = APR_HOOK_MIDDLE;
    const char *endp = ap_strrchr_c(line, '>');

    if (endp == NULL) {
        return apr_pstrcat(cmd->pool, cmd->cmd->name,
                           "> directive missing closing '>'", NULL);
    }

    line = apr_pstrndup(cmd->temp_pool, line, endp - line);

    if (line[0]) { 
        const char *word;
        word = ap_getword_conf(cmd->temp_pool, &line);
        if (*word) {
            function = apr_pstrdup(cmd->pool, word);
        }
        word = ap_getword_conf(cmd->temp_pool, &line);
        if (*word) {
            if (!strcasecmp("early", word)) { 
                when = AP_LUA_HOOK_FIRST;
            }
            else if (!strcasecmp("late", word)) {
                when = AP_LUA_HOOK_LAST;
            }
            else { 
                return apr_pstrcat(cmd->pool, cmd->cmd->name,
                                   "> 2nd argument must be 'early' or 'late'", NULL);
            }
        }
    }

    spec = apr_pcalloc(cmd->pool, sizeof(ap_lua_mapped_handler_spec));

    {
        cr_ctx ctx;
        lua_State *lvm;
        char *tmp;
        int rv;
        ap_directive_t **current;
        hack_section_baton *baton;

        spec->file_name = apr_psprintf(cmd->pool, "%s:%u",
                                       cmd->config_file->name,
                                       cmd->config_file->line_number);
        if (function) {
            spec->function_name = (char *) function;
        }
        else {
            function = NULL;
        }

        ctx.cmd = cmd;
        tmp = apr_pstrdup(cmd->pool, cmd->err_directive->directive + 1);
        ap_str_tolower(tmp);
        ctx.endstr = tmp;
        ctx.cfp = cmd->config_file;
        ctx.startline = cmd->config_file->line_number;

        /* This lua State is used only to compile the input strings -> bytecode, so we don't need anything extra. */
        lvm = luaL_newstate();

        lua_settop(lvm, 0);

        rv = lua_load(lvm, direct_chunkreader, &ctx, spec->file_name);

        if (rv != 0) {
            const char *errstr = apr_pstrcat(cmd->pool, "Lua Error:",
                                             lua_tostring(lvm, -1), NULL);
            lua_close(lvm);
            return errstr;
        }
        else {
            luaL_Buffer b;
            luaL_buffinit(lvm, &b);
#if LUA_VERSION_NUM >= 503
            lua_dump(lvm, ldump_writer, &b, 0);
#else
            lua_dump(lvm, ldump_writer, &b);
#endif
            luaL_pushresult(&b);
            spec->bytecode_len = lua_strlen(lvm, -1);
            spec->bytecode = apr_pstrmemdup(cmd->pool, lua_tostring(lvm, -1),
                                            spec->bytecode_len);
            lua_close(lvm);
        }

        current = mconfig;

        /* Here, we have to replace our current config node for the next pass */
        if (!*current) {
            *current = apr_pcalloc(cmd->pool, sizeof(**current));
        }

        baton = apr_pcalloc(cmd->pool, sizeof(hack_section_baton));
        baton->name = name;
        baton->spec = spec;
        baton->apr_hook_when = when;

        (*current)->filename = cmd->config_file->name;
        (*current)->line_num = cmd->config_file->line_number;
        (*current)->directive = apr_pstrdup(cmd->pool, "Lua_____ByteCodeHack");
        (*current)->args = NULL;
        (*current)->data = baton;
    }

    return NULL;
}
static const char *register_named_block_function_hook(const char *name,
                                                      cmd_parms *cmd,
                                                      void *mconfig,
                                                      const char *line)
{
    const char *function;
    ap_lua_mapped_handler_spec *spec;

    if (line && line[0] == '>') {
        function = NULL;
    }
    else {
        const char *word;
        apr_size_t wordlen;
        word = ap_getword_conf(cmd->pool, &line);
        wordlen = strlen(word);
        if (wordlen == 0 || word[wordlen - 1] != '>') {
            return apr_pstrcat(cmd->pool, cmd->directive->directive,
                               "> takes exactly one argument", NULL);
        }
        else {
            function = apr_pstrndup(cmd->pool, word, wordlen - 1);
        }
    }

    spec = apr_pcalloc(cmd->pool, sizeof(ap_lua_mapped_handler_spec));

    {
        cr_ctx ctx;
        char buf[32];
        lua_State *lvm;
        char *tmp;
        int rv;
        ap_directive_t **current;
        hack_section_baton *baton;

        apr_snprintf(buf, sizeof(buf), "%u", cmd->config_file->line_number);
        spec->file_name =
            apr_pstrcat(cmd->pool, cmd->config_file->name, ":", buf, NULL);
        if (function) {
            spec->function_name = (char *) function;
        }
        else {
            function = NULL;
        }
        spec->code_cache_style = APL_CODE_CACHE_FOREVER;

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
            const char *errstr =
                apr_pstrcat(cmd->pool, "Lua Error:", lua_tostring(lvm, -1),
                            NULL);
            lua_close(lvm);
            return errstr;
        }
        else {
            luaL_Buffer b;
            luaL_buffinit(lvm, &b);
            lua_dump(lvm, ldump_writer, &b);
            luaL_pushresult(&b);
            spec->bytecode_len = lua_strlen(lvm, -1);
            spec->bytecode =
                apr_pstrmemdup(cmd->pool, lua_tostring(lvm, -1),
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

        (*current)->filename = cmd->config_file->name;
        (*current)->line_num = cmd->config_file->line_number;
        (*current)->directive =
            apr_pstrdup(cmd->pool, "Lua_____ByteCodeHack");
        (*current)->args = NULL;
        (*current)->data = baton;
    }

    return NULL;
}
static const char *define_filter(cmd_parms *cmd, void *dummy, const char *args)
{
    ef_server_t *conf = ap_get_module_config(cmd->server->module_config,
                                             &ext_filter_module);
    const char *token;
    const char *name;
    char *normalized_name;
    ef_filter_t *filter;

    name = ap_getword_white(cmd->pool, &args);
    if (!name) {
        return "Filter name not found";
    }

    /* During request processing, we find information about the filter
     * by looking up the filter name provided by core server in our
     * hash table.  But the core server has normalized the filter
     * name by converting it to lower case.  Thus, when adding the
     * filter to our hash table we have to use lower case as well.
     */
    normalized_name = apr_pstrdup(cmd->pool, name);
    ap_str_tolower(normalized_name);

    if (apr_hash_get(conf->h, normalized_name, APR_HASH_KEY_STRING)) {
        return apr_psprintf(cmd->pool, "ExtFilter %s is already defined",
                            name);
    }

    filter = (ef_filter_t *)apr_pcalloc(conf->p, sizeof(ef_filter_t));
    filter->name = name;
    filter->mode = OUTPUT_FILTER;
    filter->ftype = AP_FTYPE_RESOURCE;
    apr_hash_set(conf->h, normalized_name, APR_HASH_KEY_STRING, filter);

    while (*args) {
        while (apr_isspace(*args)) {
            ++args;
        }

        /* Nasty parsing...  I wish I could simply use ap_getword_white()
         * here and then look at the token, but ap_getword_white() doesn't
         * do the right thing when we have cmd="word word word"
         */
        if (!strncasecmp(args, "preservescontentlength", 22)) {
            token = ap_getword_white(cmd->pool, &args);
            if (!strcasecmp(token, "preservescontentlength")) {
                filter->preserves_content_length = 1;
            }
            else {
                return apr_psprintf(cmd->pool,
                                    "mangled argument `%s'",
                                    token);
            }
            continue;
        }

        if (!strncasecmp(args, "mode=", 5)) {
            args += 5;
            token = ap_getword_white(cmd->pool, &args);
            if (!strcasecmp(token, "output")) {
                filter->mode = OUTPUT_FILTER;
            }
            else if (!strcasecmp(token, "input")) {
                filter->mode = INPUT_FILTER;
            }
            else {
                return apr_psprintf(cmd->pool, "Invalid mode: `%s'",
                                    token);
            }
            continue;
        }

        if (!strncasecmp(args, "ftype=", 6)) {
            args += 6;
            token = ap_getword_white(cmd->pool, &args);
            filter->ftype = atoi(token);
            continue;
        }

        if (!strncasecmp(args, "enableenv=", 10)) {
            args += 10;
            token = ap_getword_white(cmd->pool, &args);
            filter->enable_env = token;
            continue;
        }

        if (!strncasecmp(args, "disableenv=", 11)) {
            args += 11;
            token = ap_getword_white(cmd->pool, &args);
            filter->disable_env = token;
            continue;
        }

        if (!strncasecmp(args, "intype=", 7)) {
            args += 7;
            filter->intype = ap_getword_white(cmd->pool, &args);
            continue;
        }

        if (!strncasecmp(args, "outtype=", 8)) {
            args += 8;
            filter->outtype = ap_getword_white(cmd->pool, &args);
            continue;
        }

        if (!strncasecmp(args, "cmd=", 4)) {
            args += 4;
            if ((token = parse_cmd(cmd->pool, &args, filter))) {
                return token;
            }
            continue;
        }

        return apr_psprintf(cmd->pool, "Unexpected parameter: `%s'",
                            args);
    }

    /* parsing is done...  register the filter
     */
    if (filter->mode == OUTPUT_FILTER) {
        /* XXX need a way to ensure uniqueness among all filters */
        ap_register_output_filter(filter->name, ef_outpu
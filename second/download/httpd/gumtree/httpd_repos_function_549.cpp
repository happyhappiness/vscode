static const char *add_setenvif_core(cmd_parms *cmd, void *mconfig,
                                     char *fname, const char *args)
{
    char *regex;
    const char *simple_pattern;
    const char *feature;
    sei_cfg_rec *sconf;
    sei_entry *new;
    sei_entry *entries;
    char *var;
    int i;
    int beenhere = 0;
    int icase;

    /*
     * Determine from our context into which record to put the entry.
     * cmd->path == NULL means we're in server-wide context; otherwise,
     * we're dealing with a per-directory setting.
     */
    sconf = (cmd->path != NULL)
      ? (sei_cfg_rec *) mconfig
      : (sei_cfg_rec *) ap_get_module_config(cmd->server->module_config,
                                               &setenvif_module);
    entries = (sei_entry *) sconf->conditionals->elts;
    /* get regex */
    regex = ap_getword_conf(cmd->pool, &args);
    if (!*regex) {
        return apr_pstrcat(cmd->pool, "Missing regular expression for ",
                           cmd->cmd->name, NULL);
    }

    /*
     * If we've already got a sei_entry with the same name we want to
     * just copy the name pointer... so that later on we can compare
     * two header names just by comparing the pointers.
     */
    for (i = 0; i < sconf->conditionals->nelts; ++i) {
        new = &entries[i];
        if (!strcasecmp(new->name, fname)) {
            fname = new->name;
            break;
        }
    }

    /* if the last entry has an identical headername and regex then
     * merge with it
     */
    i = sconf->conditionals->nelts - 1;
    icase = cmd->info == ICASE_MAGIC;
    if (i < 0
        || entries[i].name != fname
        || entries[i].icase != icase
        || strcmp(entries[i].regex, regex)) {

        /* no match, create a new entry */
        new = apr_array_push(sconf->conditionals);
        new->name = fname;
        new->regex = regex;
        new->icase = icase;
        if ((simple_pattern = non_regex_pattern(cmd->pool, regex))) {
            new->pattern = apr_strmatch_precompile(cmd->pool,
                                                   simple_pattern, !icase);
            if (new->pattern == NULL) {
                return apr_pstrcat(cmd->pool, cmd->cmd->name,
                                   " pattern could not be compiled.", NULL);
            }
            new->preg = NULL;
        }
        else {
            new->preg = ap_pregcomp(cmd->pool, regex,
                                    (AP_REG_EXTENDED | (icase ? AP_REG_ICASE : 0)));
            if (new->preg == NULL) {
                return apr_pstrcat(cmd->pool, cmd->cmd->name,
                                   " regex could not be compiled.", NULL);
            }
            new->pattern = NULL;
        }
        new->features = apr_table_make(cmd->pool, 2);

        if (!strcasecmp(fname, "remote_addr")) {
            new->special_type = SPECIAL_REMOTE_ADDR;
        }
        else if (!strcasecmp(fname, "remote_host")) {
            new->special_type = SPECIAL_REMOTE_HOST;
        }
        else if (!strcasecmp(fname, "request_uri")) {
            new->special_type = SPECIAL_REQUEST_URI;
        }
        else if (!strcasecmp(fname, "request_method")) {
            new->special_type = SPECIAL_REQUEST_METHOD;
        }
        else if (!strcasecmp(fname, "request_protocol")) {
            new->special_type = SPECIAL_REQUEST_PROTOCOL;
        }
        else if (!strcasecmp(fname, "server_addr")) {
            new->special_type = SPECIAL_SERVER_ADDR;
        }
        else if (!strncasecmp(fname, "oid(",4)) {
            ap_regmatch_t match[AP_MAX_REG_MATCH];

            new->special_type = SPECIAL_OID_VALUE;

            /* Syntax check and extraction of the OID as a regex: */
            new->pnamereg = ap_pregcomp(cmd->pool,
                                        "^oid\\(\"?([0-9.]+)\"?\\)$",
                                        (AP_REG_EXTENDED /* | AP_REG_NOSUB */
                                         | AP_REG_ICASE));
            /* this can never happen, as long as pcre works:
              if (new->pnamereg == NULL)
                    return apr_pstrcat(cmd->pool, cmd->cmd->name,
                                       "OID regex could not be compiled.", NULL);
             */
            if (ap_regexec(new->pnamereg, fname, AP_MAX_REG_MATCH, match, 0) == AP_REG_NOMATCH) {
                return apr_pstrcat(cmd->pool, cmd->cmd->name,
                                       "OID syntax is: oid(\"1.2.3.4.5\"); error in: ",
                                       fname, NULL);
            }
            new->pnamereg = NULL;
            /* The name field is used for the stripped oid string */
            new->name = fname = apr_pstrdup(cmd->pool, fname+match[1].rm_so);
            fname[match[1].rm_eo - match[1].rm_so] = '\0';
        }
        else {
            new->special_type = SPECIAL_NOT;
            /* Handle fname as a regular expression.
             * If fname a simple header string, identify as such
             * (new->pnamereg = NULL) to avoid the overhead of searching
             * through headers_in for a regex match.
             */
            if (is_header_regex(cmd->pool, fname)) {
                new->pnamereg = ap_pregcomp(cmd->pool, fname,
                                            (AP_REG_EXTENDED | AP_REG_NOSUB
                                             | (icase ? AP_REG_ICASE : 0)));
                if (new->pnamereg == NULL)
                    return apr_pstrcat(cmd->pool, cmd->cmd->name,
                                       "Header name regex could not be "
                                       "compiled.", NULL);
            }
            else {
                new->pnamereg = NULL;
            }
        }
    }
    else {
        new = &entries[i];
    }

    for ( ; ; ) {
        feature = ap_getword_conf(cmd->pool, &args);
        if (!*feature) {
            break;
        }
        beenhere++;

        var = ap_getword(cmd->pool, &feature, '=');
        if (*feature) {
            apr_table_setn(new->features, var, feature);
        }
        else if (*var == '!') {
            apr_table_setn(new->features, var + 1, "!");
        }
        else {
            apr_table_setn(new->features, var, "1");
        }
    }

    if (!beenhere) {
        return apr_pstrcat(cmd->pool, "Missing envariable expression for ",
                           cmd->cmd->name, NULL);
    }

    return NULL;
}
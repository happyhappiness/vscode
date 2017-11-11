static const char *cmd_rewriterule(cmd_parms *cmd, void *in_dconf,
                                   const char *in_str)
{
    rewrite_perdir_conf *dconf = in_dconf;
    char *str = apr_pstrdup(cmd->pool, in_str);
    rewrite_server_conf *sconf;
    rewriterule_entry *newrule;
    regex_t *regexp;
    char *a1;
    char *a2;
    char *a3;
    char *cp;
    const char *err;
    int mode;

    sconf = ap_get_module_config(cmd->server->module_config, &rewrite_module);

    /*  make a new entry in the internal rewrite rule list */
    if (cmd->path == NULL) {   /* is server command */
        newrule = apr_array_push(sconf->rewriterules);
    }
    else {                     /* is per-directory command */
        newrule = apr_array_push(dconf->rewriterules);
    }

    /*  parse the argument line ourself */
    if (parseargline(str, &a1, &a2, &a3)) {
        return apr_pstrcat(cmd->pool, "RewriteRule: bad argument line '", str,
                          "'", NULL);
    }

    /* arg3: optional flags field */
    newrule->forced_mimetype     = NULL;
    newrule->forced_responsecode = HTTP_MOVED_TEMPORARILY;
    newrule->flags  = RULEFLAG_NONE;
    newrule->env[0] = NULL;
    newrule->cookie[0] = NULL;
    newrule->skip   = 0;
    if (a3 != NULL) {
        if ((err = cmd_rewriterule_parseflagfield(cmd->pool, newrule,
                                                  a3)) != NULL) {
            return err;
        }
    }

    /*  arg1: the pattern
     *  try to compile the regexp to test if is ok
     */
    cp = a1;
    if (cp[0] == '!') {
        newrule->flags |= RULEFLAG_NOTMATCH;
        cp++;
    }
    mode = REG_EXTENDED;
    if (newrule->flags & RULEFLAG_NOCASE) {
        mode |= REG_ICASE;
    }
    if ((regexp = ap_pregcomp(cmd->pool, cp, mode)) == NULL) {
        return apr_pstrcat(cmd->pool,
                          "RewriteRule: cannot compile regular expression '",
                          a1, "'", NULL);
    }
    newrule->pattern = apr_pstrdup(cmd->pool, cp);
    newrule->regexp  = regexp;

    /*  arg2: the output string
     *  replace the $<N> by \<n> which is needed by the currently
     *  used Regular Expression library
     *
     * TODO: Is this still required for PCRE?  If not, does it *work* with PCRE?
     */
    newrule->output = apr_pstrdup(cmd->pool, a2);

    /* now, if the server or per-dir config holds an
     * array of RewriteCond entries, we take it for us
     * and clear the array
     */
    if (cmd->path == NULL) {  /* is server command */
        newrule->rewriteconds   = sconf->rewriteconds;
        sconf->rewriteconds = apr_array_make(cmd->pool, 2,
                                            sizeof(rewritecond_entry));
    }
    else {                    /* is per-directory command */
        newrule->rewriteconds   = dconf->rewriteconds;
        dconf->rewriteconds = apr_array_make(cmd->pool, 2,
                                            sizeof(rewritecond_entry));
    }

    return NULL;
}
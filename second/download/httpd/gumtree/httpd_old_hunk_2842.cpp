}

/* need prototype for overlap check */
static int alias_matches(const char *uri, const char *alias_fakename);

static const char *add_alias_internal(cmd_parms *cmd, void *dummy,
                                      const char *f, const char *r,
                                      int use_regex)
{
    server_rec *s = cmd->server;
    alias_server_conf *conf = ap_get_module_config(s->module_config,
                                                   &alias_module);
    alias_entry *new = apr_array_push(conf->aliases);
    alias_entry *entries = (alias_entry *)conf->aliases->elts;
    int i;

    /* XX r can NOT be relative to DocumentRoot here... compat bug. */

    if (use_regex) {
        new->regexp = ap_pregcomp(cmd->pool, f, AP_REG_EXTENDED);
        if (new->regexp == NULL)
            return "Regular expression could not be compiled.";
        new->real = r;
    }
    else {
        /* XXX This may be optimized, but we must know that new->real
         * exists.  If so, we can dir merge later, trusing new->real
         * and just canonicalizing the remainder.  Not till I finish
         * cleaning out the old ap_canonical stuff first.
         */
        new->real = r;
    }
    new->fake = f;
    new->handler = cmd->info;

    /* check for overlapping (Script)Alias directives
     * and throw a warning if found one
     */
    if (!use_regex) {
        for (i = 0; i < conf->aliases->nelts - 1; ++i) {
            alias_entry *p = &entries[i];

            if (  (!p->regexp &&  alias_matches(f, p->fake) > 0)
                || (p->regexp && !ap_regexec(p->regexp, f, 0, NULL, 0))) {
                ap_log_error(APLOG_MARK, APLOG_WARNING, 0, cmd->server,
                             "The %s directive in %s at line %d will probably "
                             "never match because it overlaps an earlier "
                             "%sAlias%s.",
                             cmd->cmd->name, cmd->directive->filename,
                             cmd->directive->line_num,
                             p->handler ? "Script" : "",
                             p->regexp ? "Match" : "");

                break; /* one warning per alias should be sufficient */
            }
        }
    }

    return NULL;
}

static const char *add_alias(cmd_parms *cmd, void *dummy, const char *f,
                             const char *r)
{
    return add_alias_internal(cmd, dummy, f, r, 0);
}

static const char *add_alias_regex(cmd_parms *cmd, void *dummy, const char *f,
                                   const char *r)
{
    return add_alias_internal(cmd, dummy, f, r, 1);
}

static const char *add_redirect_internal(cmd_parms *cmd,
                                         alias_dir_conf *dirconf,
                                         const char *arg1, const char *arg2,
                                         const char *arg3, int use_regex)

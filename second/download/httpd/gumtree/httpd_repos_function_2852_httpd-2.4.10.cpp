static const char *add_authz_section(cmd_parms *cmd, void *mconfig,
                                     const char *args)
{
    authz_core_dir_conf *conf = mconfig;
    const char *endp = ap_strrchr_c(args, '>');
    authz_section_conf *old_section = conf->section;
    authz_section_conf *section;
    int old_overrides = cmd->override;
    apr_int64_t old_limited = cmd->limited;
    const char *errmsg;

    if (endp == NULL) {
        return apr_pstrcat(cmd->pool, cmd->cmd->name,
                           "> directive missing closing '>'", NULL);
    }

    args = apr_pstrndup(cmd->temp_pool, args, endp - args);

    if (args[0]) {
        return apr_pstrcat(cmd->pool, cmd->cmd->name,
                           "> directive doesn't take additional arguments",
                           NULL);
    }

    section = apr_pcalloc(cmd->pool, sizeof(*section));

    if (!strcasecmp(cmd->cmd->name, "<RequireAll")) {
        section->op = AUTHZ_LOGIC_AND;
    }
    else if (!strcasecmp(cmd->cmd->name, "<RequireAny")) {
        section->op = AUTHZ_LOGIC_OR;
    }
    else if (!strcasecmp(cmd->cmd->name, "<RequireNotAll")) {
        section->op = AUTHZ_LOGIC_AND;
        section->negate = 1;
    }
    else {
        section->op = AUTHZ_LOGIC_OR;
        section->negate = 1;
    }

    conf->section = section;

    /* trigger NOT_IN_LIMIT errors as if this were a <Limit> directive */
    cmd->limited &= ~(AP_METHOD_BIT << (METHODS - 1));

    cmd->override = OR_AUTHCFG;
    errmsg = ap_walk_config(cmd->directive->first_child, cmd, cmd->context);
    cmd->override = old_overrides;

    cmd->limited = old_limited;

    conf->section = old_section;

    if (errmsg) {
        return errmsg;
    }

    if (section->first) {
        authz_section_conf *child;

        if (!old_section) {
            old_section = conf->section = create_default_section(cmd->pool);
        }

        if (section->negate && old_section->op == AUTHZ_LOGIC_OR) {
            return apr_psprintf(cmd->pool, "%s directive has "
                                "no effect in %s directive",
                                format_authz_command(cmd->pool, section),
                                format_authz_command(cmd->pool, old_section));
        }

        old_section->limited |= section->limited;

        if (!section->negate && section->op == old_section->op) {
            /* be associative */
            section = section->first;
        }

        child = old_section->first;

        if (child) {
            while (child->next) {
                child = child->next;
            }

            child->next = section;
        }
        else {
            old_section->first = section;
        }
    }
    else {
        return apr_pstrcat(cmd->pool,
                           format_authz_command(cmd->pool, section),
                           " directive contains no authorization directives",
                           NULL);
    }

    return NULL;
}
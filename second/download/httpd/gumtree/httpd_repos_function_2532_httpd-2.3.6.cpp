static const char *add_authz_provider(cmd_parms *cmd, void *config,
                                      const char *args)
{
    authz_core_dir_conf *conf = (authz_core_dir_conf*)config;
    authz_section_conf *section = apr_pcalloc(cmd->pool, sizeof(*section));
    authz_section_conf *child;

    section->provider_name = ap_getword_conf(cmd->pool, &args);

    if (!strcasecmp(section->provider_name, "not")) {
        section->provider_name = ap_getword_conf(cmd->pool, &args);
        section->negate = 1;
    }

    section->provider_args = args;

    /* lookup and cache the actual provider now */
    section->provider = ap_lookup_provider(AUTHZ_PROVIDER_GROUP,
                                           section->provider_name,
                                           AUTHZ_PROVIDER_VERSION);

    /* by the time the config file is used, the provider should be loaded
     * and registered with us.
     */
    if (!section->provider) {
        return apr_psprintf(cmd->pool,
                            "Unknown Authz provider: %s",
                            section->provider_name);
    }

    /* if the provider doesn't provide the appropriate function, reject it */
    if (!section->provider->check_authorization) {
        return apr_psprintf(cmd->pool,
                            "The '%s' Authz provider is not supported by any "
                            "of the loaded authorization modules",
                            section->provider_name);
    }

    section->limited = cmd->limited;

    if (!conf->section) {
        conf->section = create_default_section(cmd->pool);
    }

    if (section->negate && conf->section->op == AUTHZ_LOGIC_OR) {
        return apr_psprintf(cmd->pool, "negative %s directive has no effect "
                            "in %s directive",
                            cmd->cmd->name,
                            format_authz_command(cmd->pool, conf->section));
    }

    conf->section->limited |= section->limited;

    child = conf->section->first;

    if (child) {
        while (child->next) {
            child = child->next;
        }

        child->next = section;
    }
    else {
        conf->section->first = section;
    }

    return NULL;
}
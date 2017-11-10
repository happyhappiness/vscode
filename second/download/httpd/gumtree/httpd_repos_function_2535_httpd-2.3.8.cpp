static const char *authz_require_alias_section(cmd_parms *cmd, void *mconfig,
                                               const char *args)
{
    const char *endp = ap_strrchr_c(args, '>');
    char *provider_name;
    char *provider_alias;
    char *provider_args;
    ap_conf_vector_t *new_authz_config;
    int old_overrides = cmd->override;
    const char *errmsg;

    const char *err = ap_check_cmd_context(cmd, GLOBAL_ONLY);
    if (err != NULL) {
        return err;
    }

    if (endp == NULL) {
        return apr_pstrcat(cmd->pool, cmd->cmd->name,
                           "> directive missing closing '>'", NULL);
    }

    args = apr_pstrndup(cmd->pool, args, endp - args);

    if (!args[0]) {
        return apr_pstrcat(cmd->pool, cmd->cmd->name,
                           "> directive requires additional arguments", NULL);
    }

    /* Pull the real provider name and the alias name from the block header */
    provider_name = ap_getword_conf(cmd->pool, &args);
    provider_alias = ap_getword_conf(cmd->pool, &args);
    provider_args = ap_getword_conf(cmd->pool, &args);

    if (!provider_name[0] || !provider_alias[0]) {
        return apr_pstrcat(cmd->pool, cmd->cmd->name,
                           "> directive requires additional arguments", NULL);
    }

    new_authz_config = ap_create_per_dir_config(cmd->pool);

    /* Walk the subsection configuration to get the per_dir config that we will
     * merge just before the real provider is called.
     */
    cmd->override = OR_AUTHCFG | ACCESS_CONF;
    errmsg = ap_walk_config(cmd->directive->first_child, cmd,
                            new_authz_config);
    cmd->override = old_overrides;

    if (!errmsg) {
        provider_alias_rec *prvdraliasrec;
        authz_core_srv_conf *authcfg;

        prvdraliasrec = apr_pcalloc(cmd->pool, sizeof(*prvdraliasrec));

        /* Save off the new directory config along with the original
         * provider name and function pointer data
         */
        prvdraliasrec->provider_name = provider_name;
        prvdraliasrec->provider_alias = provider_alias;
        prvdraliasrec->provider_args = provider_args;
        prvdraliasrec->sec_auth = new_authz_config;
        prvdraliasrec->provider =
            ap_lookup_provider(AUTHZ_PROVIDER_GROUP, provider_name,
                               AUTHZ_PROVIDER_VERSION);

        /* by the time the config file is used, the provider should be loaded
         * and registered with us.
         */
        if (!prvdraliasrec->provider) {
            return apr_psprintf(cmd->pool,
                                "Unknown Authz provider: %s",
                                provider_name);
        }

        authcfg = ap_get_module_config(cmd->server->module_config,
                                       &authz_core_module);

        apr_hash_set(authcfg->alias_rec, provider_alias,
                     APR_HASH_KEY_STRING, prvdraliasrec);

        /* Register the fake provider so that we get called first */
        ap_register_auth_provider(cmd->pool, AUTHZ_PROVIDER_GROUP,
                                  provider_alias, AUTHZ_PROVIDER_VERSION,
                                  &authz_alias_provider,
                                  AP_AUTH_INTERNAL_PER_CONF);
    }

    return errmsg;
}
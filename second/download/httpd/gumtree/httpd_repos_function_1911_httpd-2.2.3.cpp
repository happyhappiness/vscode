static const char *authaliassection(cmd_parms *cmd, void *mconfig, const char *arg)
{
    int old_overrides = cmd->override;
    const char *endp = ap_strrchr_c(arg, '>');
    const char *args;
    char *provider_alias;
    char *provider_name;
    const char *errmsg;
    const authn_provider *provider = NULL;
    ap_conf_vector_t *new_auth_config = ap_create_per_dir_config(cmd->pool);
    authn_alias_srv_conf *authcfg =
        (authn_alias_srv_conf *)ap_get_module_config(cmd->server->module_config,
                                                     &authn_alias_module);

    const char *err = ap_check_cmd_context(cmd, GLOBAL_ONLY);
    if (err != NULL) {
        return err;
    }

    if (endp == NULL) {
        return apr_pstrcat(cmd->pool, cmd->cmd->name,
                           "> directive missing closing '>'", NULL);
    }

    args = apr_pstrndup(cmd->pool, arg, endp - arg);

    if (!args[0]) {
        return apr_pstrcat(cmd->pool, cmd->cmd->name,
                           "> directive requires additional arguments", NULL);
    }

    /* Pull the real provider name and the alias name from the block header */
    provider_name = ap_getword_conf(cmd->pool, &args);
    provider_alias = ap_getword_conf(cmd->pool, &args);

    if (!provider_name[0] || !provider_alias[0]) {
        return apr_pstrcat(cmd->pool, cmd->cmd->name,
                           "> directive requires additional arguments", NULL);
    }

    if (strcasecmp(provider_name, provider_alias) == 0) {
        return apr_pstrcat(cmd->pool,
                           "The alias provider name must be different from the base provider name.", NULL);
    }

    /* Look up the alias provider to make sure that it hasn't already been registered. */
    provider = ap_lookup_provider(AUTHN_PROVIDER_GROUP, provider_alias, "0");
    if (provider) {
        return apr_pstrcat(cmd->pool, "The alias provider ", provider_alias,
                           " has already be registered previously as either a base provider or an alias provider.",
                           NULL);
    }

    /* walk the subsection configuration to get the per_dir config that we will
       merge just before the real provider is called. */
    cmd->override = OR_ALL|ACCESS_CONF;
    errmsg = ap_walk_config(cmd->directive->first_child, cmd, new_auth_config);

    if (!errmsg) {
        provider_alias_rec *prvdraliasrec = apr_pcalloc(cmd->pool, sizeof(provider_alias_rec));
        provider = ap_lookup_provider(AUTHN_PROVIDER_GROUP, provider_name, "0");

        /* Save off the new directory config along with the original provider name
           and function pointer data */
        prvdraliasrec->sec_auth = new_auth_config;
        prvdraliasrec->provider_name = provider_name;
        prvdraliasrec->provider_alias = provider_alias;
        prvdraliasrec->provider = provider;
        apr_hash_set(authcfg->alias_rec, provider_alias, APR_HASH_KEY_STRING, prvdraliasrec);

        /* Register the fake provider so that we get called first */
        ap_register_provider(cmd->pool, AUTHN_PROVIDER_GROUP, provider_alias, "0",
                             &authn_alias_provider);
    }

    cmd->override = old_overrides;

    return errmsg;
}
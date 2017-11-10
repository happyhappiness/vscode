static authn_status authn_alias_check_password(request_rec *r, const char *user,
                                              const char *password)
{
    /* Look up the provider alias in the alias list */
    /* Get the dir_config and call ap_Merge_per_dir_configs() */
    /* Call the real provider->check_password() function */
    /* return the result of the above function call */

    const char *provider_name = apr_table_get(r->notes, AUTHN_PROVIDER_NAME_NOTE);
    authn_status ret = AUTH_USER_NOT_FOUND;
    authn_alias_srv_conf *authcfg =
        (authn_alias_srv_conf *)ap_get_module_config(r->server->module_config,
                                                     &authn_core_module);

    if (provider_name) {
        provider_alias_rec *prvdraliasrec = apr_hash_get(authcfg->alias_rec,
                                                         provider_name, APR_HASH_KEY_STRING);
        ap_conf_vector_t *orig_dir_config = r->per_dir_config;

        /* If we found the alias provider in the list, then merge the directory
           configurations and call the real provider */
        if (prvdraliasrec) {
            r->per_dir_config = ap_merge_per_dir_configs(r->pool, orig_dir_config,
                                                         prvdraliasrec->sec_auth);
            ret = prvdraliasrec->provider->check_password(r,user,password);
            r->per_dir_config = orig_dir_config;
        }
    }

    return ret;
}
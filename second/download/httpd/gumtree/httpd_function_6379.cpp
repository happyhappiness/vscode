static authz_status authz_alias_check_authorization(request_rec *r,
                                                    const char *require_args,
                                                    const void *parsed_require_args)
{
    const char *provider_name;
    authz_status ret = AUTHZ_DENIED;

    /* Look up the provider alias in the alias list.
     * Get the the dir_config and call ap_Merge_per_dir_configs()
     * Call the real provider->check_authorization() function
     * return the result of the above function call
     */

    provider_name = apr_table_get(r->notes, AUTHZ_PROVIDER_NAME_NOTE);

    if (provider_name) {
        authz_core_srv_conf *authcfg;
        provider_alias_rec *prvdraliasrec;

        authcfg = ap_get_module_config(r->server->module_config,
                                       &authz_core_module);

        prvdraliasrec = apr_hash_get(authcfg->alias_rec, provider_name,
                                     APR_HASH_KEY_STRING);

        /* If we found the alias provider in the list, then merge the directory
           configurations and call the real provider */
        if (prvdraliasrec) {
            ap_conf_vector_t *orig_dir_config = r->per_dir_config;

            r->per_dir_config =
                ap_merge_per_dir_configs(r->pool, orig_dir_config,
                                         prvdraliasrec->sec_auth);

            ret = prvdraliasrec->provider->
                check_authorization(r, prvdraliasrec->provider_args,
                                    prvdraliasrec->provider_parsed_args);

            r->per_dir_config = orig_dir_config;
        }
        else {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(02305)
                          "no alias provider found for '%s' (BUG?)",
                          provider_name);
        }
    }
    else {
        ap_assert(provider_name != NULL);
    }

    return ret;
}
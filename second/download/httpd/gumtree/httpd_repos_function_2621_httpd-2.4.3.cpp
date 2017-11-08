static void register_hooks(apr_pool_t *p)
{
    authz_owner_get_file_group = APR_RETRIEVE_OPTIONAL_FN(authz_owner_get_file_group);

    ap_register_auth_provider(p, AUTHZ_PROVIDER_GROUP, "dbm-group",
                              AUTHZ_PROVIDER_VERSION,
                              &authz_dbmgroup_provider,
                              AP_AUTH_INTERNAL_PER_CONF);
    ap_register_auth_provider(p, AUTHZ_PROVIDER_GROUP, "dbm-file-group",
                              AUTHZ_PROVIDER_VERSION,
                              &authz_dbmfilegroup_provider,
                              AP_AUTH_INTERNAL_PER_CONF);
}
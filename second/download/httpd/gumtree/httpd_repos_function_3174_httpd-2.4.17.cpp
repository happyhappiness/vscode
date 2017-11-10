static void register_hooks(apr_pool_t *p)
{
    ap_register_auth_provider(p, AUTHZ_PROVIDER_GROUP, "dbm-group",
                              AUTHZ_PROVIDER_VERSION,
                              &authz_dbmgroup_provider,
                              AP_AUTH_INTERNAL_PER_CONF);
    ap_register_auth_provider(p, AUTHZ_PROVIDER_GROUP, "dbm-file-group",
                              AUTHZ_PROVIDER_VERSION,
                              &authz_dbmfilegroup_provider,
                              AP_AUTH_INTERNAL_PER_CONF);
    ap_hook_optional_fn_retrieve(authz_dbm_getfns, NULL, NULL, APR_HOOK_MIDDLE);
}
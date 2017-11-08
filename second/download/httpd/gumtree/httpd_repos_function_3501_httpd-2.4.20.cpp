static void register_hooks(apr_pool_t *p)
{
    ap_register_auth_provider(p, AUTHZ_PROVIDER_GROUP, "group",
                              AUTHZ_PROVIDER_VERSION,
                              &authz_group_provider,
                              AP_AUTH_INTERNAL_PER_CONF);
    ap_register_auth_provider(p, AUTHZ_PROVIDER_GROUP, "file-group",
                              AUTHZ_PROVIDER_VERSION,
                              &authz_filegroup_provider,
                              AP_AUTH_INTERNAL_PER_CONF);
    ap_hook_optional_fn_retrieve(authz_groupfile_getfns, NULL, NULL, APR_HOOK_MIDDLE);
}
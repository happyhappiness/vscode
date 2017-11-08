static void register_hooks(apr_pool_t *p)
{
    APR_REGISTER_OPTIONAL_FN(authz_owner_get_file_group);

    ap_register_auth_provider(p, AUTHZ_PROVIDER_GROUP, "file-owner",
                              AUTHZ_PROVIDER_VERSION,
                              &authz_fileowner_provider,
                              AP_AUTH_INTERNAL_PER_CONF);
}
static void register_hooks(apr_pool_t *p)
{
    ap_register_auth_provider(p, AUTHZ_PROVIDER_GROUP, "user",
                              AUTHZ_PROVIDER_VERSION,
                              &authz_user_provider, AP_AUTH_INTERNAL_PER_CONF);
    ap_register_auth_provider(p, AUTHZ_PROVIDER_GROUP, "valid-user",
                              AUTHZ_PROVIDER_VERSION,
                              &authz_validuser_provider,
                              AP_AUTH_INTERNAL_PER_CONF);
}
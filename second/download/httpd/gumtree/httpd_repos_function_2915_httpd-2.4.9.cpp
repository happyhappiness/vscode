static void authz_dbd_hooks(apr_pool_t *p)
{
    ap_register_auth_provider(p, AUTHZ_PROVIDER_GROUP, "dbd-group",
                              AUTHZ_PROVIDER_VERSION,
                              &authz_dbdgroup_provider,
                              AP_AUTH_INTERNAL_PER_CONF);
    ap_register_auth_provider(p, AUTHZ_PROVIDER_GROUP, "dbd-login",
                              AUTHZ_PROVIDER_VERSION,
                              &authz_dbdlogin_provider,
                              AP_AUTH_INTERNAL_PER_CONF);
    ap_register_auth_provider(p, AUTHZ_PROVIDER_GROUP, "dbd-logout",
                              AUTHZ_PROVIDER_VERSION,
                              &authz_dbdlogout_provider,
                              AP_AUTH_INTERNAL_PER_CONF);
}
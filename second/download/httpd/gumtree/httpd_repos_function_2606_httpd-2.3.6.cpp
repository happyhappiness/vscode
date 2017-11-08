static void register_hooks(apr_pool_t *p)
{
    ap_register_auth_provider(p, AUTHZ_PROVIDER_GROUP, "env",
                              AUTHZ_PROVIDER_VERSION,
                              &authz_env_provider, AP_AUTH_INTERNAL_PER_CONF);
    ap_register_auth_provider(p, AUTHZ_PROVIDER_GROUP, "ip",
                              AUTHZ_PROVIDER_VERSION,
                              &authz_ip_provider, AP_AUTH_INTERNAL_PER_CONF);
    ap_register_auth_provider(p, AUTHZ_PROVIDER_GROUP, "host",
                              AUTHZ_PROVIDER_VERSION,
                              &authz_host_provider, AP_AUTH_INTERNAL_PER_CONF);
    ap_register_auth_provider(p, AUTHZ_PROVIDER_GROUP, "all",
                              AUTHZ_PROVIDER_VERSION,
                              &authz_all_provider, AP_AUTH_INTERNAL_PER_CONF);
}
static void register_hooks(apr_pool_t *p)
{
    ap_hook_pre_config(authz_host_pre_config, NULL, NULL, APR_HOOK_MIDDLE);
    ap_hook_post_config(authz_host_post_config, NULL, NULL, APR_HOOK_MIDDLE);

    ap_register_auth_provider(p, AUTHZ_PROVIDER_GROUP, "ip",
                              AUTHZ_PROVIDER_VERSION,
                              &authz_ip_provider, AP_AUTH_INTERNAL_PER_CONF);
    ap_register_auth_provider(p, AUTHZ_PROVIDER_GROUP, "host",
                              AUTHZ_PROVIDER_VERSION,
                              &authz_host_provider, AP_AUTH_INTERNAL_PER_CONF);
    ap_register_auth_provider(p, AUTHZ_PROVIDER_GROUP, "forward-dns",
                              AUTHZ_PROVIDER_VERSION,
                              &authz_forward_dns_provider,
                              AP_AUTH_INTERNAL_PER_CONF);
    ap_register_auth_provider(p, AUTHZ_PROVIDER_GROUP, "local",
                              AUTHZ_PROVIDER_VERSION,
                              &authz_local_provider, AP_AUTH_INTERNAL_PER_CONF);
}
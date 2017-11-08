static void register_hooks(apr_pool_t *p)
{
    ap_register_auth_provider(p, AUTHN_PROVIDER_GROUP, "anon",
                              AUTHN_PROVIDER_VERSION,
                              &authn_anon_provider, AP_AUTH_INTERNAL_PER_CONF);
}
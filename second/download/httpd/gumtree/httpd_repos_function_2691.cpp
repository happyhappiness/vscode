static void register_hooks(apr_pool_t *p)
{
    ap_register_auth_provider(p, AUTHN_PROVIDER_GROUP, "socache",
                              AUTHN_PROVIDER_VERSION,
                              &authn_cache_provider, AP_AUTH_INTERNAL_PER_CONF);
    APR_REGISTER_OPTIONAL_FN(ap_authn_cache_store);
    ap_hook_pre_config(authn_cache_precfg, NULL, NULL, APR_HOOK_MIDDLE);
    ap_hook_post_config(authn_cache_post_config, NULL, NULL, APR_HOOK_MIDDLE);
    ap_hook_child_init(authn_cache_child_init, NULL, NULL, APR_HOOK_MIDDLE);
}
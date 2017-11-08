static void cache_socache_register_hook(apr_pool_t *p)
{
    /* cache initializer */
    ap_register_provider(p, CACHE_PROVIDER_GROUP, "socache", "0",
            &cache_socache_provider);
    ap_hook_pre_config(socache_precfg, NULL, NULL, APR_HOOK_MIDDLE);
    ap_hook_post_config(socache_post_config, NULL, NULL, APR_HOOK_MIDDLE);
    ap_hook_child_init(socache_child_init, NULL, NULL, APR_HOOK_MIDDLE);
}
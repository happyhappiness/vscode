static void register_hooks(apr_pool_t *p)
{
    ap_register_provider(p, AP_SERF_CLUSTER_PROVIDER,
                         "heartbeat", "0", &builtin_heartbeat);

    ap_register_provider(p, AP_SERF_CLUSTER_PROVIDER,
                         "static", "0", &builtin_static);

    ap_hook_post_config(serf_post_config, NULL, NULL, APR_HOOK_MIDDLE);

    ap_hook_handler(serf_handler, NULL, NULL, APR_HOOK_FIRST);
}
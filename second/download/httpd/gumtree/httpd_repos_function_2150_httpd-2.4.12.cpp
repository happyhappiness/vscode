static void register_hooks(apr_pool_t *p)
{
    static const char * const aszPred[]={ "mod_heartmonitor.c", NULL };
    ap_register_provider(p, PROXY_LBMETHOD, "heartbeat", "0", &heartbeat);
    ap_hook_post_config(lb_hb_init, aszPred, NULL, APR_HOOK_MIDDLE);
}
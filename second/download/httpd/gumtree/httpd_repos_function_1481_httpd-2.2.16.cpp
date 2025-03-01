static void ap_proxy_balancer_register_hook(apr_pool_t *p)
{
    /* Only the mpm_winnt has child init hook handler.
     * make sure that we are called after the mpm
     * initializes and after the mod_proxy
     */
    static const char *const aszPred[] = { "mpm_winnt.c", "mod_proxy.c", NULL};
     /* manager handler */
    ap_hook_post_config(balancer_init, NULL, NULL, APR_HOOK_MIDDLE);
    ap_hook_handler(balancer_handler, NULL, NULL, APR_HOOK_FIRST);
    ap_hook_child_init(child_init, aszPred, NULL, APR_HOOK_MIDDLE);
    proxy_hook_pre_request(proxy_balancer_pre_request, NULL, NULL, APR_HOOK_FIRST);
    proxy_hook_post_request(proxy_balancer_post_request, NULL, NULL, APR_HOOK_FIRST);
    proxy_hook_canon_handler(proxy_balancer_canon, NULL, NULL, APR_HOOK_FIRST);
    ap_register_provider(p, PROXY_LBMETHOD, "bytraffic", "0", &bytraffic);
    ap_register_provider(p, PROXY_LBMETHOD, "byrequests", "0", &byrequests);
    ap_register_provider(p, PROXY_LBMETHOD, "bybusyness", "0", &bybusyness);
}
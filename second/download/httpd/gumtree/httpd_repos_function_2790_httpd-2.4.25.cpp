static void register_hook(apr_pool_t *p)
{
    ap_hook_post_config(h2_proxy_post_config, NULL, NULL, APR_HOOK_MIDDLE);

    proxy_hook_scheme_handler(proxy_http2_handler, NULL, NULL, APR_HOOK_FIRST);
    proxy_hook_canon_handler(proxy_http2_canon, NULL, NULL, APR_HOOK_FIRST);
}
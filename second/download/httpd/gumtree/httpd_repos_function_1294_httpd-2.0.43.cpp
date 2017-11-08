static void ap_proxy_connect_register_hook(apr_pool_t *p)
{
    proxy_hook_scheme_handler(ap_proxy_connect_handler, NULL, NULL, APR_HOOK_MIDDLE);
    proxy_hook_canon_handler(ap_proxy_connect_canon, NULL, NULL, APR_HOOK_MIDDLE);
}
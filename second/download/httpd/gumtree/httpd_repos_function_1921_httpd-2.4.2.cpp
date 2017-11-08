static void register_hooks(apr_pool_t *p)
{
    proxy_hook_scheme_handler(scgi_handler, NULL, NULL, APR_HOOK_FIRST);
    proxy_hook_canon_handler(scgi_canon, NULL, NULL, APR_HOOK_FIRST);
    APR_OPTIONAL_HOOK(proxy, request_status, scgi_request_status, NULL, NULL,
                      APR_HOOK_MIDDLE);
}
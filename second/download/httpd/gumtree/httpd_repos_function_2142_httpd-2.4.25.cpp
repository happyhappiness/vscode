static void register_hooks(apr_pool_t *p)
{
    ap_register_provider(p, PROXY_FDPASS_FLUSHER, "flush", "0", &builtin_flush);
    proxy_hook_scheme_handler(proxy_fdpass_handler, NULL, NULL, APR_HOOK_FIRST);
    proxy_hook_canon_handler(proxy_fdpass_canon, NULL, NULL, APR_HOOK_FIRST);
}
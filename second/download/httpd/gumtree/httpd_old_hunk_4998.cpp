        if (status != OK)
            backend->close = 1;
        ap_proxy_http_cleanup(proxy_function, r, backend);
    }
    return status;
}
static void ap_proxy_http_register_hook(apr_pool_t *p)
{
    proxy_hook_scheme_handler(proxy_http_handler, NULL, NULL, APR_HOOK_FIRST);
    proxy_hook_canon_handler(proxy_http_canon, NULL, NULL, APR_HOOK_FIRST);
    warn_rx = ap_pregcomp(p, "[0-9]{3}[ \t]+[^ \t]+[ \t]+\"[^\"]*\"([ \t]+\"([^\"]+)\")?", 0);
}

AP_DECLARE_MODULE(proxy_http) = {

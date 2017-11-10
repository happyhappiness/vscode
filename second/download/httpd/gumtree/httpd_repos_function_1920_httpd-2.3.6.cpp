static void ap_proxy_rr_register_hook(apr_pool_t *p)
{
    ap_register_provider(p, PROXY_LBMETHOD, "roundrobin", "0", &roundrobin);
}
static void register_hook(apr_pool_t *p)
{
    /* Only the mpm_winnt has child init hook handler.
     * make sure that we are called after the mpm
     * initializes and after the mod_proxy
     */
    ap_register_provider(p, PROXY_LBMETHOD, "byrequests", "0", &byrequests);
}
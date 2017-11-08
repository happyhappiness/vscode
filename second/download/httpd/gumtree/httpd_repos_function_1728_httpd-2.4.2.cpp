static int post_config(apr_pool_t *p,
                       apr_pool_t *plog,
                       apr_pool_t *ptemp,
                       server_rec *s)
{
    proxy_available = (ap_find_linked_module("mod_proxy.c") != NULL);
    return OK;
}
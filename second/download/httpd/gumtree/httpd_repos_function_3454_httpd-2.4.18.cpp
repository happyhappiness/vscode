static void *authn_dbd_cr_conf(apr_pool_t *pool, char *dummy)
{
    authn_dbd_conf *ret = apr_pcalloc(pool, sizeof(authn_dbd_conf));
    return ret;
}
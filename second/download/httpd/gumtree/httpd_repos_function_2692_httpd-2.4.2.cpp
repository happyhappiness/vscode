static void *authz_dbd_cr_cfg(apr_pool_t *pool, char *dummy)
{
    authz_dbd_cfg *ret = apr_pcalloc(pool, sizeof(authz_dbd_cfg));
    ret->redirect = -1;
    return ret;
}
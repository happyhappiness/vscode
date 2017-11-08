static int nwssl_pre_config(apr_pool_t *pconf, apr_pool_t *plog,
                            apr_pool_t *ptemp)
{
    ap_seclisteners = NULL;
    ap_seclistenersup = NULL;
    certlist = apr_array_make(pconf, 1, sizeof(char *));

    return OK;
}
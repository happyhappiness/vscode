static int exipc_pre_config(apr_pool_t *pconf, apr_pool_t *plog, 
                            apr_pool_t *ptemp)
{
    ap_mutex_register(pconf, exipc_mutex_type, NULL, APR_LOCK_DEFAULT, 0);
    return OK;
}
static int hc_pre_config(apr_pool_t *pconf, apr_pool_t *plog,
                         apr_pool_t *ptemp)
{
    tpsize = HC_THREADPOOL_SIZE;
    return OK;
}
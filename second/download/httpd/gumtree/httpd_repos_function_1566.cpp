static int http_post_config(apr_pool_t *p, apr_pool_t *plog, apr_pool_t *ptemp, server_rec *s)
{
    if (ap_mpm_query(AP_MPMQ_IS_ASYNC, &async_mpm) != APR_SUCCESS) {
        async_mpm = 0;
    }
    return OK;
}
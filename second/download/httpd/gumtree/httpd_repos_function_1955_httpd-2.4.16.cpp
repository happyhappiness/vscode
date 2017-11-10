static int balancer_pre_config(apr_pool_t *pconf, apr_pool_t *plog,
                               apr_pool_t *ptemp)
{

    apr_status_t rv;

    rv = ap_mutex_register(pconf, balancer_mutex_type, NULL,
                               APR_LOCK_DEFAULT, 0);
    if (rv != APR_SUCCESS) {
        return rv;
    }

    return OK;
}
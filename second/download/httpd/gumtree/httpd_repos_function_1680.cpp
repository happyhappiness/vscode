static int serf_post_config(apr_pool_t *p, apr_pool_t *plog, apr_pool_t *ptemp, server_rec *s)
{
    apr_status_t rv;
    rv = ap_mpm_query(AP_MPMQ_HAS_SERF, &mpm_supprts_serf);

    if (rv != APR_SUCCESS) {
        mpm_supprts_serf = 0;
    }
    
    return OK; 
}
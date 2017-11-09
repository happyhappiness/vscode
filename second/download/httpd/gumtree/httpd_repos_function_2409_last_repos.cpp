static void h2_child_init(apr_pool_t *pool, server_rec *s)
{
    /* Set up our connection processing */
    apr_status_t status = h2_conn_child_init(pool, s);
    if (status != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_ERR, status, s,
                     APLOGNO(02949) "initializing connection handling");
    }
    
}
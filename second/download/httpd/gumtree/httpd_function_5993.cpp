static int proxy_pass_brigade(apr_bucket_alloc_t *bucket_alloc,
                              proxy_conn_rec *p_conn,
                              conn_rec *origin, apr_bucket_brigade *bb,
                              int flush)
{
    apr_status_t status;
    apr_off_t transferred;

    if (flush) {
        apr_bucket *e = apr_bucket_flush_create(bucket_alloc);
        APR_BRIGADE_INSERT_TAIL(bb, e);
    }
    apr_brigade_length(bb, 0, &transferred);
    if (transferred != -1)
        p_conn->worker->s->transferred += transferred;
    status = ap_pass_brigade(origin->output_filters, bb);
    /* Cleanup the brigade now to avoid buckets lifetime
     * issues in case of error returned below. */
    apr_brigade_cleanup(bb);
    if (status != APR_SUCCESS) {
        ap_log_cerror(APLOG_MARK, APLOG_ERR, status, origin, APLOGNO(03357)
                      "pass output failed to %pI (%s)",
                      p_conn->addr, p_conn->hostname);
    }
    return status;
}
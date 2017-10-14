static apr_status_t pass_brigade(apr_bucket_alloc_t *bucket_alloc,
                                 request_rec *r, proxy_http_conn_t *p_conn,
                                 conn_rec *origin, apr_bucket_brigade *bb,
                                 int flush)
{
    apr_status_t status;

    if (flush) {
        apr_bucket *e = apr_bucket_flush_create(bucket_alloc);
        APR_BRIGADE_INSERT_TAIL(bb, e);
    }
    status = ap_pass_brigade(origin->output_filters, bb);
    if (status != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_ERR, status, r->server,
                     "proxy: pass request body failed to %pI (%s)",
                     p_conn->addr, p_conn->name);
        return status;
    }
    apr_brigade_cleanup(bb);
    return APR_SUCCESS;
}
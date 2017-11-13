static apr_status_t drain_available_output(ap_filter_t *f)
{
    request_rec *r = f->r;
    conn_rec *c = r->connection;
    ef_ctx_t *ctx = f->ctx;
    ef_dir_t *dc = ctx->dc;
    apr_size_t len;
    char buf[4096];
    apr_status_t rv;
    apr_bucket_brigade *bb;
    apr_bucket *b;

    while (1) {
        len = sizeof(buf);
        rv = apr_file_read(ctx->proc->out,
                      buf,
                      &len);
        if ((rv && !APR_STATUS_IS_EAGAIN(rv)) ||
            dc->debug >= DBGLVL_GORY) {
            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, rv, r,
                          "apr_file_read(child output), len %" APR_SIZE_T_FMT,
                          !rv ? len : -1);
        }
        if (rv != APR_SUCCESS) {
            return rv;
        }
        bb = apr_brigade_create(r->pool, c->bucket_alloc);
        b = apr_bucket_transient_create(buf, len, c->bucket_alloc);
        APR_BRIGADE_INSERT_TAIL(bb, b);
        if ((rv = ap_pass_brigade(f->next, bb)) != APR_SUCCESS) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
                          "ap_pass_brigade()");
            return rv;
        }
    }
    /* we should never get here; if we do, a bogus error message would be
     * the least of our problems 
     */
    return APR_ANONYMOUS;
}
static apr_status_t send_downstream(ap_filter_t *f, const char *tmp, apr_size_t len)
{
    request_rec *r = f->r;
    conn_rec *c = r->connection;
    apr_bucket_brigade *bb;
    apr_bucket *b;
    charset_filter_ctx_t *ctx = f->ctx;
    apr_status_t rv;

    bb = apr_brigade_create(r->pool, c->bucket_alloc);
    b = apr_bucket_transient_create(tmp, len, c->bucket_alloc);
    APR_BRIGADE_INSERT_TAIL(bb, b);
    rv = ap_pass_brigade(f->next, bb);
    if (rv != APR_SUCCESS) {
        ctx->ees = EES_DOWNSTREAM;
    }
    return rv;
}
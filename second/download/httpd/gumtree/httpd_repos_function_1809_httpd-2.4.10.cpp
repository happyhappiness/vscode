static apr_status_t bail_out_on_error(http_ctx_t *ctx,
                                      ap_filter_t *f,
                                      int http_error)
{
    apr_bucket *e;
    apr_bucket_brigade *bb = ctx->bb;

    apr_brigade_cleanup(bb);

    if (f->r->proxyreq == PROXYREQ_RESPONSE) {
        switch (http_error) {
        case HTTP_REQUEST_ENTITY_TOO_LARGE:
            return APR_ENOSPC;

        case HTTP_REQUEST_TIME_OUT:
            return APR_INCOMPLETE;

        case HTTP_NOT_IMPLEMENTED:
            return APR_ENOTIMPL;

        default:
            return APR_EGENERAL;
        }
    }

    e = ap_bucket_error_create(http_error,
                               NULL, f->r->pool,
                               f->c->bucket_alloc);
    APR_BRIGADE_INSERT_TAIL(bb, e);
    e = apr_bucket_eos_create(f->c->bucket_alloc);
    APR_BRIGADE_INSERT_TAIL(bb, e);
    ctx->eos_sent = 1;
    /* If chunked encoding / content-length are corrupt, we may treat parts
     * of this request's body as the next one's headers.
     * To be safe, disable keep-alive.
     */
    f->r->connection->keepalive = AP_CONN_CLOSE;
    return ap_pass_brigade(f->r->output_filters, bb);
}
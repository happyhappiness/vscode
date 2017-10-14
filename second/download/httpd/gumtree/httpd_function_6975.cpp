static int hc_read_body (sctx_t *ctx, request_rec *r)
{
    apr_status_t rv = APR_SUCCESS;
    apr_bucket_brigade *bb;
    int seen_eos = 0;

    bb = apr_brigade_create(r->pool, r->connection->bucket_alloc);
    do {
        apr_bucket *bucket, *cpy;
        apr_size_t len = HUGE_STRING_LEN;

        rv = ap_get_brigade(r->proto_input_filters, bb, AP_MODE_READBYTES,
                            APR_BLOCK_READ, len);

        if (rv != APR_SUCCESS) {
            if (APR_STATUS_IS_TIMEUP(rv) || APR_STATUS_IS_EOF(rv)) {
                rv = APR_SUCCESS;
                break;
            }
            ap_log_error(APLOG_MARK, APLOG_DEBUG, rv, ctx->s, APLOGNO(03300)
                          "Error reading response body");
            break;
        }

        for (bucket = APR_BRIGADE_FIRST(bb);
             bucket != APR_BRIGADE_SENTINEL(bb);
             bucket = APR_BUCKET_NEXT(bucket))
        {
            if (APR_BUCKET_IS_EOS(bucket)) {
                seen_eos = 1;
                break;
            }
            if (APR_BUCKET_IS_FLUSH(bucket)) {
                continue;
            }
            rv =  apr_bucket_copy(bucket, &cpy);
            if (rv != APR_SUCCESS) {
                break;
            }
            APR_BRIGADE_INSERT_TAIL(r->kept_body, cpy);
        }
        apr_brigade_cleanup(bb);
    }
    while (!seen_eos);
    return (rv == APR_SUCCESS ? OK : !OK);
}
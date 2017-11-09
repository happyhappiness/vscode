static int hc_read_body(request_rec *r, apr_bucket_brigade *bb)
{
    apr_status_t rv = APR_SUCCESS;
    int seen_eos = 0;

    do {
        apr_size_t len = HUGE_STRING_LEN;

        apr_brigade_cleanup(bb);
        rv = ap_get_brigade(r->proto_input_filters, bb, AP_MODE_READBYTES,
                            APR_BLOCK_READ, len);

        if (rv != APR_SUCCESS) {
            if (APR_STATUS_IS_EOF(rv)) {
                rv = APR_SUCCESS;
                break;
            }
            ap_log_error(APLOG_MARK, APLOG_DEBUG, rv, r->server, APLOGNO(03300)
                          "Error reading response body");
            break;
        }

        while (!APR_BRIGADE_EMPTY(bb)) {
            apr_bucket *bucket = APR_BRIGADE_FIRST(bb);
            if (APR_BUCKET_IS_EOS(bucket)) {
                seen_eos = 1;
                break;
            }
            if (APR_BUCKET_IS_FLUSH(bucket)) {
                apr_bucket_delete(bucket);
                continue;
            }
            APR_BUCKET_REMOVE(bucket);
            APR_BRIGADE_INSERT_TAIL(r->kept_body, bucket);
        }
    }
    while (!seen_eos);
    apr_brigade_cleanup(bb);
    return (rv == APR_SUCCESS ? OK : !OK);
}
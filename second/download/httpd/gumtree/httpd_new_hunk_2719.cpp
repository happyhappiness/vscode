    if (readbytes > ctx->remaining) {
        readbytes = ctx->remaining;
    }

    /* send part of the kept_body */
    if ((rv = apr_brigade_partition(kept_body, ctx->offset, &ec)) != APR_SUCCESS) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r, APLOGNO(01414)
                      "apr_brigade_partition() failed on kept_body at %" APR_OFF_T_FMT, ctx->offset);
        return rv;
    }
    if ((rv = apr_brigade_partition(kept_body, ctx->offset + readbytes, &e2)) != APR_SUCCESS) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r, APLOGNO(01415)
                      "apr_brigade_partition() failed on kept_body at %" APR_OFF_T_FMT, ctx->offset + readbytes);
        return rv;
    }

    do {
        apr_bucket *foo;

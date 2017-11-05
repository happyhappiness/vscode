static apr_status_t kept_body_filter(ap_filter_t *f, apr_bucket_brigade *b,
                                     ap_input_mode_t mode,
                                     apr_read_type_e block,
                                     apr_off_t readbytes)
{
    request_rec *r = f->r;
    apr_bucket_brigade *kept_body = r->kept_body;
    kept_body_ctx_t *ctx = f->ctx;
    apr_bucket *ec, *e2;
    apr_status_t rv;

    /* just get out of the way of things we don't want. */
    if (!kept_body || (mode != AP_MODE_READBYTES && mode != AP_MODE_GETLINE)) {
        return ap_get_brigade(f->next, b, mode, block, readbytes);
    }

    /* set up the context if it does not already exist */
    if (!ctx) {
        f->ctx = ctx = apr_palloc(f->r->pool, sizeof(*ctx));
        ctx->offset = 0;
        apr_brigade_length(kept_body, 1, &ctx->remaining);
    }

    /* kept_body is finished, send next filter */
    if (ctx->remaining <= 0) {
        return ap_get_brigade(f->next, b, mode, block, readbytes);
    }

    /* send all of the kept_body, but no more */
    if (readbytes > ctx->remaining) {
        readbytes = ctx->remaining;
    }

    /* send part of the kept_body */
    if ((rv = apr_brigade_partition(kept_body, ctx->offset, &ec)) != APR_SUCCESS) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
                      "apr_brigade_partition() failed on kept_body at %" APR_OFF_T_FMT, ctx->offset);
        return rv;
    }
    if ((rv = apr_brigade_partition(kept_body, ctx->offset + readbytes, &e2)) != APR_SUCCESS) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
                      "apr_brigade_partition() failed on kept_body at %" APR_OFF_T_FMT, ctx->offset + readbytes);
        return rv;
    }

    do {
        apr_bucket *foo;
        const char *str;
        apr_size_t len;

        if (apr_bucket_copy(ec, &foo) != APR_SUCCESS) {
            /* As above; this should not fail since the bucket has
             * a known length, but just to be sure, this takes
             * care of uncopyable buckets that do somehow manage
             * to slip through.  */
            /* XXX: check for failure? */
            apr_bucket_read(ec, &str, &len, APR_BLOCK_READ);
            apr_bucket_copy(ec, &foo);
        }
        APR_BRIGADE_INSERT_TAIL(b, foo);
        ec = APR_BUCKET_NEXT(ec);
    } while (ec != e2);

    ctx->remaining -= readbytes;
    ctx->offset += readbytes;
    return APR_SUCCESS;

}
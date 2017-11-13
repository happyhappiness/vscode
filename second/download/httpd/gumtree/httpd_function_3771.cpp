static apr_status_t keep_body_filter(ap_filter_t *f, apr_bucket_brigade *b,
                                     ap_input_mode_t mode,
                                     apr_read_type_e block,
                                     apr_off_t readbytes)
{
    apr_bucket *e;
    keep_body_ctx_t *ctx = f->ctx;
    apr_status_t rv;
    apr_bucket *bucket;
    apr_off_t len = 0;


    if (!ctx) {
        const char *lenp;
        char *endstr = NULL;
        request_dir_conf *dconf = ap_get_module_config(f->r->per_dir_config,
                                                       &request_module);

        /* must we step out of the way? */
        if (!dconf->keep_body || f->r->kept_body) {
            ap_remove_input_filter(f);
            return ap_get_brigade(f->next, b, mode, block, readbytes);
        }

        f->ctx = ctx = apr_pcalloc(f->r->pool, sizeof(*ctx));

        /* fail fast if the content length exceeds keep body */
        lenp = apr_table_get(f->r->headers_in, "Content-Length");
        if (lenp) {

            /* Protects against over/underflow, non-digit chars in the
             * string (excluding leading space) (the endstr checks)
             * and a negative number. */
            if (apr_strtoff(&ctx->remaining, lenp, &endstr, 10)
                || endstr == lenp || *endstr || ctx->remaining < 0) {

                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, f->r,
                              "Invalid Content-Length");

                ap_remove_input_filter(f);
                return bail_out_on_error(b, f, HTTP_REQUEST_ENTITY_TOO_LARGE);
            }

            /* If we have a limit in effect and we know the C-L ahead of
             * time, stop it here if it is invalid.
             */
            if (dconf->keep_body < ctx->remaining) {
                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, f->r,
                          "Requested content-length of %" APR_OFF_T_FMT
                          " is larger than the configured limit"
                          " of %" APR_OFF_T_FMT, ctx->remaining, dconf->keep_body);
                ap_remove_input_filter(f);
                return bail_out_on_error(b, f, HTTP_REQUEST_ENTITY_TOO_LARGE);
            }

        }

        f->r->kept_body = apr_brigade_create(f->r->pool, f->r->connection->bucket_alloc);
        ctx->remaining = dconf->keep_body;

    }

    /* get the brigade from upstream, and read it in to get its length */
    rv = ap_get_brigade(f->next, b, mode, block, readbytes);
    if (rv == APR_SUCCESS) {
        rv = apr_brigade_length(b, 1, &len);
    }

    /* does the length take us over the limit? */
    if (APR_SUCCESS == rv && len > ctx->remaining) {
        if (f->r->kept_body) {
            apr_brigade_cleanup(f->r->kept_body);
            f->r->kept_body = NULL;
        }
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, f->r,
                      "Requested content-length of %" APR_OFF_T_FMT
                      " is larger than the configured limit"
                      " of %" APR_OFF_T_FMT, len, ctx->keep_body);
        return bail_out_on_error(b, f, HTTP_REQUEST_ENTITY_TOO_LARGE);
    }
    ctx->remaining -= len;

    /* pass any errors downstream */
    if (rv != APR_SUCCESS) {
        if (f->r->kept_body) {
            apr_brigade_cleanup(f->r->kept_body);
            f->r->kept_body = NULL;
        }
        return rv;
    }

    /* all is well, set aside the buckets */
    for (bucket = APR_BRIGADE_FIRST(b);
         bucket != APR_BRIGADE_SENTINEL(b);
         bucket = APR_BUCKET_NEXT(bucket))
    {
        apr_bucket_copy(bucket, &e);
        APR_BRIGADE_INSERT_TAIL(f->r->kept_body, e);
    }

    return APR_SUCCESS;
}
    /* does the length take us over the limit? */
    if (APR_SUCCESS == rv && len > ctx->remaining) {
        if (f->r->kept_body) {
            apr_brigade_cleanup(f->r->kept_body);
            f->r->kept_body = NULL;
        }
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, f->r, APLOGNO(01413)
                      "Requested content-length of %" APR_OFF_T_FMT
                      " is larger than the configured limit"
                      " of %" APR_OFF_T_FMT, len, ctx->keep_body);
        return bail_out_on_error(b, f, HTTP_REQUEST_ENTITY_TOO_LARGE);
    }
    ctx->remaining -= len;

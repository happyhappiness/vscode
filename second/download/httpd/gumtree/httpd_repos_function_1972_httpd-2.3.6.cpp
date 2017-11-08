static apr_status_t ef_output_filter(ap_filter_t *f, apr_bucket_brigade *bb)
{
    request_rec *r = f->r;
    ef_ctx_t *ctx = f->ctx;
    apr_status_t rv;

    if (!ctx) {
        if ((rv = init_filter_instance(f)) != APR_SUCCESS) {
            ctx = f->ctx;
            ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
                          "can't initialise output filter %s: %s",
                          f->frec->name,
                          (ctx->dc->onfail == 1) ? "removing" : "aborting");
            ap_remove_output_filter(f);
            if (ctx->dc->onfail == 1) {
                return ap_pass_brigade(f->next, bb);
            }
            else {
                apr_bucket *e;
                f->r->status_line = "500 Internal Server Error";

                apr_brigade_cleanup(bb);
                e = ap_bucket_error_create(HTTP_INTERNAL_SERVER_ERROR,
                                           NULL, r->pool,
                                           f->c->bucket_alloc);
                APR_BRIGADE_INSERT_TAIL(bb, e);
                e = apr_bucket_eos_create(f->c->bucket_alloc);
                APR_BRIGADE_INSERT_TAIL(bb, e);
                ap_pass_brigade(f->next, bb);
                return AP_FILTER_ERROR;
            }
        }
        ctx = f->ctx;
    }
    if (ctx->noop) {
        ap_remove_output_filter(f);
        return ap_pass_brigade(f->next, bb);
    }

    rv = ef_unified_filter(f, bb);
    if (rv != APR_SUCCESS) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
                      "ef_unified_filter() failed");
    }

    if ((rv = ap_pass_brigade(f->next, bb)) != APR_SUCCESS) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
                      "ap_pass_brigade() failed");
    }
    return rv;
}
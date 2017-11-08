static apr_status_t ef_output_filter(ap_filter_t *f, apr_bucket_brigade *bb)
{
    request_rec *r = f->r;
    ef_ctx_t *ctx = f->ctx;
    apr_status_t rv;

    if (!ctx) {
        if ((rv = init_filter_instance(f)) != APR_SUCCESS) {
            return rv;
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
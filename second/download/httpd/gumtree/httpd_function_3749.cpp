static apr_status_t handle_endif(include_ctx_t *ctx, ap_filter_t *f,
                                 apr_bucket_brigade *bb)
{
    request_rec *r = f->r;

    if (ctx->argc) {
        ap_log_rerror(APLOG_MARK,
                      (!(ctx->if_nesting_level)) ? APLOG_ERR : APLOG_WARNING,
                      0, r, "endif directive does not take tags in %s",
                      r->filename);
    }

    if (ctx->if_nesting_level) {
        --(ctx->if_nesting_level);
        return APR_SUCCESS;
    }

    if (ctx->argc) {
        SSI_CREATE_ERROR_BUCKET(ctx, f, bb);
        return APR_SUCCESS;
    }

    DEBUG_DUMP_COND(ctx, "endif");

    ctx->flags |= (SSI_FLAG_PRINTING | SSI_FLAG_COND_TRUE);

    return APR_SUCCESS;
}
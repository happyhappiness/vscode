/*
 * <!--#set var="..." value="..." ... -->
 */
static apr_status_t handle_set(include_ctx_t *ctx, ap_filter_t *f,
                               apr_bucket_brigade *bb)
{
    const char *encoding = "none", *decoding = "none";
    char *var = NULL;
    request_rec *r = f->r;
    request_rec *sub = r->main;
    apr_pool_t *p = r->pool;
    int error = 0;

    if (ctx->argc < 2) {
        ap_log_rerror(APLOG_MARK,
                      (ctx->flags & SSI_FLAG_PRINTING)
                          ? APLOG_ERR : APLOG_WARNING,
                      0, r,
                      APLOGNO(01362) "missing argument for set element in %s",
                      r->filename);
    }

    if (!(ctx->flags & SSI_FLAG_PRINTING)) {
        return APR_SUCCESS;
    }

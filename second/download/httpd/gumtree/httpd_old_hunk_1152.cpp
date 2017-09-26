{
    ef_ctx_t *ctx = f->ctx;
    apr_status_t rv;

    if (!ctx) {
        if ((rv = init_filter_instance(f)) != APR_SUCCESS) {
            return rv;
        }
        ctx = f->ctx;
    }

    if (ctx->noop) {
        ap_remove_input_filter(f);

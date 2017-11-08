static int dav_process_ctx_list(void (*func)(dav_prop_ctx *ctx),
                                apr_array_header_t *ctx_list, int stop_on_error,
                                int reverse)
{
    int i = ctx_list->nelts;
    dav_prop_ctx *ctx = (dav_prop_ctx *)ctx_list->elts;

    if (reverse)
        ctx += i;

    while (i--) {
        if (reverse)
            --ctx;

        (*func)(ctx);
        if (stop_on_error && DAV_PROP_CTX_HAS_ERR(*ctx)) {
            return 1;
        }

        if (!reverse)
            ++ctx;
    }

    return 0;
}
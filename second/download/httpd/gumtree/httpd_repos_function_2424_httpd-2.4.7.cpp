static void chk_filter_chain(ap_filter_t *f)
{
    ap_filter_t *curf;
    charset_filter_ctx_t *curctx, *last_xlate_ctx = NULL,
        *ctx = f->ctx;
    int output = !strcasecmp(f->frec->name, XLATEOUT_FILTER_NAME);

    if (ctx->noop) {
        return;
    }

    /* walk the filter chain; see if it makes sense for our filter to
     * do any translation
     */
    curf = output ? f->r->output_filters : f->r->input_filters;
    while (curf) {
        if (!strcasecmp(curf->frec->name, f->frec->name) &&
            curf->ctx) {
            curctx = (charset_filter_ctx_t *)curf->ctx;
            if (!last_xlate_ctx) {
                last_xlate_ctx = curctx;
            }
            else {
                if (strcmp(last_xlate_ctx->dc->charset_default,
                           curctx->dc->charset_source)) {
                    /* incompatible translation
                     * if our filter instance is incompatible with an instance
                     * already in place, noop our instance
                     * Notes:
                     * . We are only willing to noop our own instance.
                     * . It is possible to noop another instance which has not
                     *   yet run, but this is not currently implemented.
                     *   Hopefully it will not be needed.
                     * . It is not possible to noop an instance which has
                     *   already run.
                     */
                    if (last_xlate_ctx == f->ctx) {
                        last_xlate_ctx->noop = 1;
                        if (APLOGrtrace1(f->r)) {
                            const char *symbol = output ? "->" : "<-";

                            ap_log_rerror(APLOG_MARK, APLOG_DEBUG,
                                          0, f->r, APLOGNO(01451)
                                          "%s %s - disabling "
                                          "translation %s%s%s; existing "
                                          "translation %s%s%s",
                                          f->r->uri ? "uri" : "file",
                                          f->r->uri ? f->r->uri : f->r->filename,
                                          last_xlate_ctx->dc->charset_source,
                                          symbol,
                                          last_xlate_ctx->dc->charset_default,
                                          curctx->dc->charset_source,
                                          symbol,
                                          curctx->dc->charset_default);
                        }
                    }
                    else {
                        const char *symbol = output ? "->" : "<-";

                        ap_log_rerror(APLOG_MARK, APLOG_ERR,
                                      0, f->r, APLOGNO(01452)
                                      "chk_filter_chain() - can't disable "
                                      "translation %s%s%s; existing "
                                      "translation %s%s%s",
                                      last_xlate_ctx->dc->charset_source,
                                      symbol,
                                      last_xlate_ctx->dc->charset_default,
                                      curctx->dc->charset_source,
                                      symbol,
                                      curctx->dc->charset_default);
                    }
                    break;
                }
            }
        }
        curf = curf->next;
    }
}
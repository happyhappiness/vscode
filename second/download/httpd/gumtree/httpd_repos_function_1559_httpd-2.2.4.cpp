static apr_status_t filter_harness(ap_filter_t *f, apr_bucket_brigade *bb)
{
    apr_status_t ret;
    const char *cachecontrol;
    char *str;
    harness_ctx *ctx = f->ctx;
    ap_filter_rec_t *filter = f->frec;

    if (f->r->status != 200) {
        ap_remove_output_filter(f);
        return ap_pass_brigade(f->next, bb);
    }

    filter_trace(f->c, filter->debug, f->frec->name, bb);

    /* look up a handler function if we haven't already set it */
    if (!ctx->func) {
#ifndef NO_PROTOCOL
        if (f->r->proxyreq) {
            if (filter->proto_flags & AP_FILTER_PROTO_NO_PROXY) {
                ap_remove_output_filter(f);
                return ap_pass_brigade(f->next, bb);
            }

            if (filter->proto_flags & AP_FILTER_PROTO_TRANSFORM) {
                cachecontrol = apr_table_get(f->r->headers_out,
                                             "Cache-Control");
                if (cachecontrol) {
                    str = apr_pstrdup(f->r->pool,  cachecontrol);
                    ap_str_tolower(str);
                    if (strstr(str, "no-transform")) {
                        ap_remove_output_filter(f);
                        return ap_pass_brigade(f->next, bb);
                    }
                }
            }
        }
#endif
        if (!filter_lookup(f, filter)) {
            ap_remove_output_filter(f);
            return ap_pass_brigade(f->next, bb);
        }
    }

    /* call the content filter with its own context, then restore our
     * context
     */
    f->ctx = ctx->fctx;
    ret = ctx->func(f, bb);
    ctx->fctx = f->ctx;
    f->ctx = ctx;

    return ret;
}
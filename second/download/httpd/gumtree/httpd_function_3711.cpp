static int filter_lookup(ap_filter_t *f, ap_filter_rec_t *filter)
{
    ap_filter_provider_t *provider;
    int match;
    int err = 0;
    unsigned int proto_flags;
    request_rec *r = f->r;
    harness_ctx *ctx = f->ctx;
    provider_ctx *pctx;
#ifndef NO_PROTOCOL
    mod_filter_ctx *rctx = ap_get_module_config(r->request_config,
                                                &filter_module);
#endif

    /* Check registered providers in order */
    for (provider = filter->providers; provider; provider = provider->next) {
        match = ap_expr_eval(r, provider->expr, &err, NULL, ap_expr_string, NULL);
        if (err) {
            /* log error but accept match value ? */
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                          "Error evaluating filter dispatch condition");
        }

        if (match) {
            /* condition matches this provider */
#ifndef NO_PROTOCOL
            /* check protocol
             *
             * FIXME:
             * This is a quick hack and almost certainly buggy.
             * The idea is that by putting this in mod_filter, we relieve
             * filter implementations of the burden of fixing up HTTP headers
             * for cases that are routinely affected by filters.
             *
             * Default is ALWAYS to do nothing, so as not to tread on the
             * toes of filters which want to do it themselves.
             *
             */
            proto_flags = provider->frec->proto_flags;

            /* some specific things can't happen in a proxy */
            if (r->proxyreq) {
                if (proto_flags & AP_FILTER_PROTO_NO_PROXY) {
                    /* can't use this provider; try next */
                    continue;
                }

                if (proto_flags & AP_FILTER_PROTO_TRANSFORM) {
                    const char *str = apr_table_get(r->headers_out,
                                                    "Cache-Control");
                    if (str) {
                        char *str1 = apr_pstrdup(r->pool, str);
                        ap_str_tolower(str1);
                        if (strstr(str1, "no-transform")) {
                            /* can't use this provider; try next */
                            continue;
                        }
                    }
                    apr_table_addn(r->headers_out, "Warning",
                                   apr_psprintf(r->pool,
                                                "214 %s Transformation applied",
                                                r->hostname));
                }
            }

            /* things that are invalidated if the filter transforms content */
            if (proto_flags & AP_FILTER_PROTO_CHANGE) {
                apr_table_unset(r->headers_out, "Content-MD5");
                apr_table_unset(r->headers_out, "ETag");
                if (proto_flags & AP_FILTER_PROTO_CHANGE_LENGTH) {
                    apr_table_unset(r->headers_out, "Content-Length");
                }
            }

            /* no-cache is for a filter that has different effect per-hit */
            if (proto_flags & AP_FILTER_PROTO_NO_CACHE) {
                apr_table_unset(r->headers_out, "Last-Modified");
                apr_table_addn(r->headers_out, "Cache-Control", "no-cache");
            }

            if (proto_flags & AP_FILTER_PROTO_NO_BYTERANGE) {
                apr_table_unset(r->headers_out, "Accept-Ranges");
            }
            else if (rctx && rctx->range) {
                /* restore range header we saved earlier */
                apr_table_setn(r->headers_in, "Range", rctx->range);
                rctx->range = NULL;
            }
#endif
            for (pctx = ctx->init_ctx; pctx; pctx = pctx->next) {
                if (pctx->provider == provider) {
                    ctx->fctx = pctx->ctx ;
                }
            }
            ctx->func = provider->frec->filter_func.out_func;
            return 1;
        }
    }

    /* No provider matched */
    return 0;
}
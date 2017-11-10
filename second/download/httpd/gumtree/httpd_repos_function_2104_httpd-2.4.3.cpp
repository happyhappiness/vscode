static int filter_lookup(ap_filter_t *f, ap_filter_rec_t *filter)
{
    ap_filter_provider_t *provider;
    int match = 0;
    const char *err = NULL;
    request_rec *r = f->r;
    harness_ctx *ctx = f->ctx;
    provider_ctx *pctx;
#ifndef NO_PROTOCOL
    unsigned int proto_flags;
    mod_filter_ctx *rctx = ap_get_module_config(r->request_config,
                                                &filter_module);
#endif

    /* Check registered providers in order */
    for (provider = filter->providers; provider; provider = provider->next) {
        if (provider->expr) {
            match = ap_expr_exec(r, provider->expr, &err);
            if (err) {
                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01379)
                              "Error evaluating filter dispatch condition: %s",
                              err);
                match = 0;
            }
            ap_log_rerror(APLOG_MARK, APLOG_TRACE2, 0, r,
                          "Expression condition for '%s' %s",
                          provider->frec->name,
                          match ? "matched" : "did not match");
        }
        else if (r->content_type) {
            const char **type = provider->types;
            size_t len = strcspn(r->content_type, "; \t");
            AP_DEBUG_ASSERT(type != NULL);
            ap_log_rerror(APLOG_MARK, APLOG_TRACE4, 0, r,
                          "Content-Type '%s' ...", r->content_type);
            while (*type) {
                /* Handle 'content-type;charset=...' correctly */
                if (strncmp(*type, r->content_type, len) == 0
                    && (*type)[len] == '\0') {
                    ap_log_rerror(APLOG_MARK, APLOG_TRACE4, 0, r,
                                  "... matched '%s'", *type);
                    match = 1;
                    break;
                }
                else {
                    ap_log_rerror(APLOG_MARK, APLOG_TRACE4, 0, r,
                                  "... did not match '%s'", *type);
                }
                type++;
            }
            ap_log_rerror(APLOG_MARK, APLOG_TRACE2, 0, r,
                          "Content-Type condition for '%s' %s",
                          provider->frec->name,
                          match ? "matched" : "did not match");
        }
        else {
            ap_log_rerror(APLOG_MARK, APLOG_TRACE2, 0, r,
                          "Content-Type condition for '%s' did not match: "
                          "no Content-Type", provider->frec->name);
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
                apr_table_setn(r->headers_out, "Accept-Ranges", "none");
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
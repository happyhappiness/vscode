         * code).  This would get several different types of documents
         * translated properly: mod_autoindex output, mod_status output,
         * mod_info output, hard-coded error documents, etc.
         */
            strcmp(mime_type, DIR_MAGIC_TYPE) == 0 ||
#endif
            strncasecmp(mime_type, "message/", 8) == 0 ||
            dc->force_xlate == FX_FORCE)) {

            rv = apr_xlate_open(&ctx->xlate,
                                dc->charset_default, dc->charset_source, f->r->pool);
            if (rv != APR_SUCCESS) {
                ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, f->r, APLOGNO(01453)
                              "can't open translation %s->%s",
                              dc->charset_source, dc->charset_default);
                ctx->noop = 1;
            }
            else {
                if (apr_xlate_sb_get(ctx->xlate, &ctx->is_sb) != APR_SUCCESS) {
                    ctx->is_sb = 0;
                }
            }
        }
        else {
            ctx->noop = 1;
            if (mime_type) {
                ap_log_rerror(APLOG_MARK, APLOG_TRACE6, 0, f->r,
                              "mime type is %s; no translation selected",
                              mime_type);
            }
        }
    }

    ap_log_rerror(APLOG_MARK, APLOG_TRACE6, 0, f->r,
                  "xlate_out_filter() - "
                  "charset_source: %s charset_default: %s",
                  dc && dc->charset_source ? dc->charset_source : "(none)",
                  dc && dc->charset_default ? dc->charset_default : "(none)");

    if (!ctx->ran) {  /* filter never ran before */
        chk_filter_chain(f);
        ctx->ran = 1;
        if (!ctx->noop && !ctx->is_sb) {
            /* We're not converting between two single-byte charsets, so unset

         * indicator in the r specifying that the body is coded in the
         * implementation character set (i.e., the charset of the source
         * code).  This would get several different types of documents
         * translated properly: mod_autoindex output, mod_status output,
         * mod_info output, hard-coded error documents, etc.
         */
            strcmp(mime_type, DIR_MAGIC_TYPE) == 0 ||
#endif
            strncasecmp(mime_type, "message/", 8) == 0) {

            rv = apr_xlate_open(&ctx->xlate,
                                dc->charset_default, dc->charset_source, f->r->pool);
            if (rv != APR_SUCCESS) {
                ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, f->r,
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
            if (dc->debug >= DBGLVL_GORY) {
                ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, f->r,
                              "mime type is %s; no translation selected",
                              mime_type);
            }
        }
    }

    if (dc->debug >= DBGLVL_GORY) {
        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, f->r,
                      "xlate_out_filter() - "
                      "charset_source: %s charset_default: %s",
                      dc && dc->charset_source ? dc->charset_source : "(none)",
                      dc && dc->charset_default ? dc->charset_default : "(none)");
    }

    if (!ctx->ran) {  /* filter never ran before */
        chk_filter_chain(f);
        ctx->ran = 1;
        if (!ctx->noop && !ctx->is_sb) {
            /* We're not converting between two single-byte charsets, so unset
             * Content-Length since it is unlikely to remain the same.
             */
            apr_table_unset(f->r->headers_out, "Content-Length");
        }
    }

    if (ctx->noop) {
        return ap_pass_brigade(f->next, bb);
    }


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
        }
        else {
                ctx->noop = 1;
                if (dc->debug >= DBGLVL_GORY)
                    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, f->r,
                                  "mime type is %s; no translation selected",
                                  mime_type);
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
    }

    if (ctx->noop) {
        return ap_pass_brigade(f->next, bb);
    }


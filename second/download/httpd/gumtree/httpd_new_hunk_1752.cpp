         * code).  This would get several different types of documents
         * translated properly: mod_autoindex output, mod_status output,
         * mod_info output, hard-coded error documents, etc.
         */
            strcmp(mime_type, DIR_MAGIC_TYPE) == 0 ||
#endif
            strncasecmp(mime_type, "message/", 8) == 0 || 
            dc->force_xlate == FX_FORCE) {

            rv = apr_xlate_open(&ctx->xlate,
                                dc->charset_default, dc->charset_source, f->r->pool);
            if (rv != APR_SUCCESS) {
                ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, f->r,
                              "can't open translation %s->%s",

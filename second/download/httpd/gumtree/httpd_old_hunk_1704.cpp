                          dc->charset_default ? dc->charset_default : "unspecified");
        }
        return DECLINED;
    }

    /* catch proxy requests */
    if (r->proxyreq) return DECLINED;
    /* mod_rewrite indicators */
    if (!strncmp(r->filename, "redirect:", 9)) return DECLINED;
    if (!strncmp(r->filename, "gone:", 5)) return DECLINED;
    if (!strncmp(r->filename, "passthrough:", 12)) return DECLINED;
    if (!strncmp(r->filename, "forbidden:", 10)) return DECLINED;
    /* no translation when server and network charsets are set to the same value */
    if (!strcasecmp(dc->charset_source, dc->charset_default)) return DECLINED;

    mime_type = r->content_type ? r->content_type : ap_default_type(r);

    /* If mime type isn't text or message, bail out.
     */

/* XXX When we handle translation of the request body, watch out here as
 *     1.3 allowed additional mime types: multipart and
 *     application/x-www-form-urlencoded
 */

    if (strncasecmp(mime_type, "text/", 5) &&
#if APR_CHARSET_EBCDIC || AP_WANT_DIR_TRANSLATION
        /* On an EBCDIC machine, be willing to translate mod_autoindex-
         * generated output.  Otherwise, it doesn't look too cool.
         *
         * XXX This isn't a perfect fix because this doesn't trigger us
         * to convert from the charset of the source code to ASCII.  The
         * general solution seems to be to allow a generator to set an
         * indicator in the r specifying that the body is coded in the
         * implementation character set (i.e., the charset of the source
         * code).  This would get several different types of documents
         * translated properly: mod_autoindex output, mod_status output,
         * mod_info output, hard-coded error documents, etc.
         */
        strcmp(mime_type, DIR_MAGIC_TYPE) &&
#endif
        strncasecmp(mime_type, "message/", 8)) {
        if (dc->debug >= DBGLVL_GORY) {
            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                          "mime type is %s; no translation selected",
                          mime_type);
        }
        /* We must not bail out here (i.e., the MIME test must be in the filter
         * itself, not in the fixup, because only then is the final MIME type known.
         * Examples for late changes to the MIME type include CGI handling (MIME
         * type is set in the Content-Type header produced by the CGI script), or
         * PHP (until PHP runs, the MIME type is set to application/x-httpd-php)
         */
    }

    if (dc->debug >= DBGLVL_GORY) {
        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                      "charset_source: %s charset_default: %s",
                      dc && dc->charset_source ? dc->charset_source : "(none)",
                      dc && dc->charset_default ? dc->charset_default : "(none)");
    }

    /* Get storage for the request data and the output filter context.
     * We rarely need the input filter context, so allocate that separately.
     */
    reqinfo = (charset_req_t *)apr_pcalloc(r->pool,

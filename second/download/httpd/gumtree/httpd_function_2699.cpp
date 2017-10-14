static int find_code_page(request_rec *r)
{
    charset_dir_t *dc = ap_get_module_config(r->per_dir_config,
                                             &charset_lite_module);
    charset_req_t *reqinfo;
    charset_filter_ctx_t *input_ctx, *output_ctx;
    apr_status_t rv;
    const char *mime_type;

    if (dc->debug >= DBGLVL_FLOW) {
        ap_log_rerror(APLOG_MARK,APLOG_DEBUG, 0, r,
                      "uri: %s file: %s method: %d "
                      "imt: %s flags: %s%s%s %s->%s",
                      r->uri, r->filename, r->method_number,
                      r->content_type ? r->content_type : "(unknown)",
                      r->main     ? "S" : "",    /* S if subrequest */
                      r->prev     ? "R" : "",    /* R if redirect */
                      r->proxyreq ? "P" : "",    /* P if proxy */
                      dc->charset_source, dc->charset_default);
    }

    /* If we don't have a full directory configuration, bail out.
     */
    if (!dc->charset_source || !dc->charset_default) {
        if (dc->debug >= DBGLVL_PMC) {
            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                          "incomplete configuration: src %s, dst %s",
                          dc->charset_source ? dc->charset_source : "unspecified",
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
                                           sizeof(charset_req_t) +
                                           sizeof(charset_filter_ctx_t));
    output_ctx = (charset_filter_ctx_t *)(reqinfo + 1);

    reqinfo->dc = dc;
    output_ctx->dc = dc;
    ap_set_module_config(r->request_config, &charset_lite_module, reqinfo);

    reqinfo->output_ctx = output_ctx;

    /* We must not open the xlation table here yet, because the final MIME
     * type is not known until we are actually called in the output filter.
     * With POST or PUT request, the case is different, because their MIME
     * type is set in the request headers, and their data are prerequisites
     * for actually calling, e.g., the CGI handler later on.
     */
    output_ctx->xlate = NULL;

    switch (r->method_number) {
    case M_PUT:
    case M_POST:
        /* Set up input translation.  Note: A request body can be included
         * with the OPTIONS method, but for now we don't set up translation
         * of it.
         */
        input_ctx = apr_pcalloc(r->pool, sizeof(charset_filter_ctx_t));
        input_ctx->bb = apr_brigade_create(r->pool,
                                           r->connection->bucket_alloc);
        input_ctx->tmp = apr_palloc(r->pool, INPUT_XLATE_BUF_SIZE);
        input_ctx->dc = dc;
        reqinfo->input_ctx = input_ctx;
        rv = apr_xlate_open(&input_ctx->xlate, dc->charset_source,
                            dc->charset_default, r->pool);
        if (rv != APR_SUCCESS) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
                          "can't open translation %s->%s",
                          dc->charset_default, dc->charset_source);
            return HTTP_INTERNAL_SERVER_ERROR;
        }
    }

    return DECLINED;
}
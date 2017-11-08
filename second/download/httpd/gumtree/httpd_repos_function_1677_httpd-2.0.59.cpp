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
        return DECLINED;
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
    ap_set_module_config(r->request_conf
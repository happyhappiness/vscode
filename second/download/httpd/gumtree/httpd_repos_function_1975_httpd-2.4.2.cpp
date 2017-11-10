static saxctxt *check_filter_init (ap_filter_t *f)
{
    saxctxt *fctx;
    if (!f->ctx) {
        proxy_html_conf *cfg;
        const char *force;
        const char *errmsg = NULL;
        cfg = ap_get_module_config(f->r->per_dir_config, &proxy_html_module);
        force = apr_table_get(f->r->subprocess_env, "PROXY_HTML_FORCE");

        if (!force) {
            if (!f->r->proxyreq) {
                errmsg = "Non-proxy request; not inserting proxy-html filter";
            }
            else if (!f->r->content_type) {
                errmsg = "No content-type; bailing out of proxy-html filter";
            }
            else if (strncasecmp(f->r->content_type, "text/html", 9) &&
                     strncasecmp(f->r->content_type,
                                 "application/xhtml+xml", 21)) {
                errmsg = "Non-HTML content; not inserting proxy-html filter";
            }
        }
        if (!cfg->links) {
            errmsg = "No links configured: nothing for proxy-html filter to do";
        }

        if (errmsg) {
#ifndef GO_FASTER
            ap_log_rerror(APLOG_MARK, APLOG_TRACE1, 0, f->r, "%s", errmsg);
#endif
            ap_remove_output_filter(f);
            return NULL;
        }

        fctx = f->ctx = apr_pcalloc(f->r->pool, sizeof(saxctxt));
        fctx->f = f;
        fctx->bb = apr_brigade_create(f->r->pool,
                                      f->r->connection->bucket_alloc);
        fctx->cfg = cfg;
        apr_table_unset(f->r->headers_out, "Content-Length");

        if (cfg->interp)
            fixup_rules(fctx);
        else
            fctx->map = cfg->map;
        /* defer dealing with charset_out until after sniffing charset_in
         * so we can support setting one to t'other.
         */
    }
    return f->ctx;
}
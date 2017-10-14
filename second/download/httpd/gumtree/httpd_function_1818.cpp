static void emit_head(request_rec *r, char *header_fname, int suppress_amble,
                      int emit_xhtml, char *title)
{
    autoindex_config_rec *d;
    apr_table_t *hdrs = r->headers_in;
    apr_file_t *f = NULL;
    request_rec *rr = NULL;
    int emit_amble = 1;
    int emit_H1 = 1;
    const char *r_accept;
    const char *r_accept_enc;

    /*
     * If there's a header file, send a subrequest to look for it.  If it's
     * found and html do the subrequest, otherwise handle it
     */
    r_accept = apr_table_get(hdrs, "Accept");
    r_accept_enc = apr_table_get(hdrs, "Accept-Encoding");
    apr_table_setn(hdrs, "Accept", "text/html, text/plain");
    apr_table_unset(hdrs, "Accept-Encoding");


    if ((header_fname != NULL) && r->args) {
        header_fname = apr_pstrcat(r->pool, header_fname, "?", r->args, NULL);
    }

    if ((header_fname != NULL)
        && (rr = ap_sub_req_lookup_uri(header_fname, r, r->output_filters))
        && (rr->status == HTTP_OK)
        && (rr->filename != NULL)
        && (rr->finfo.filetype == APR_REG)) {
        /*
         * Check for the two specific cases we allow: text/html and
         * text/anything-else.  The former is allowed to be processed for
         * SSIs.
         */
        if (rr->content_type != NULL) {
            if (response_is_html(rr)) {
                ap_filter_t *f;
               /* Hope everything will work... */
                emit_amble = 0;
                emit_H1 = 0;

                if (! suppress_amble) {
                    emit_preamble(r, emit_xhtml, title);
                }
                /* This is a hack, but I can't find any better way to do this.
                 * The problem is that we have already created the sub-request,
                 * but we just inserted the OLD_WRITE filter, and the
                 * sub-request needs to pass its data through the OLD_WRITE
                 * filter, or things go horribly wrong (missing data, data in
                 * the wrong order, etc).  To fix it, if you create a
                 * sub-request and then insert the OLD_WRITE filter before you
                 * run the request, you need to make sure that the sub-request
                 * data goes through the OLD_WRITE filter.  Just steal this
                 * code.  The long-term solution is to remove the ap_r*
                 * functions.
                 */
                for (f=rr->output_filters;
                     f->frec != ap_subreq_core_filter_handle; f = f->next);
                f->next = r->output_filters;

                /*
                 * If there's a problem running the subrequest, display the
                 * preamble if we didn't do it before -- the header file
                 * didn't get displayed.
                 */
                if (ap_run_sub_req(rr) != OK) {
                    /* It didn't work */
                    emit_amble = suppress_amble;
                    emit_H1 = 1;
                }
            }
            else if (!strncasecmp("text/", rr->content_type, 5)) {
                /*
                 * If we can open the file, prefix it with the preamble
                 * regardless; since we'll be sending a <pre> block around
                 * the file's contents, any HTML header it had won't end up
                 * where it belongs.
                 */
                if (apr_file_open(&f, rr->filename, APR_READ,
                                  APR_OS_DEFAULT, r->pool) == APR_SUCCESS) {
                    emit_preamble(r, emit_xhtml, title);
                    emit_amble = 0;
                    do_emit_plain(r, f);
                    apr_file_close(f);
                    emit_H1 = 0;
                }
            }
        }
    }

    if (r_accept) {
        apr_table_setn(hdrs, "Accept", r_accept);
    }
    else {
        apr_table_unset(hdrs, "Accept");
    }

    if (r_accept_enc) {
        apr_table_setn(hdrs, "Accept-Encoding", r_accept_enc);
    }

    if (emit_amble) {
        emit_preamble(r, emit_xhtml, title);
    }
    
    d = (autoindex_config_rec *) ap_get_module_config(r->per_dir_config, &autoindex_module);
    
    if (emit_H1) {
        if (d->style_sheet != NULL) {
    	    /* Insert style id if stylesheet used */
    	    ap_rvputs(r, "  <h1 id=\"indextitle\">Index of ", title, "</h1>\n", NULL);
    	} else {
        ap_rvputs(r, "<h1>Index of ", title, "</h1>\n", NULL);
    }
    }
    if (rr != NULL) {
        ap_destroy_sub_req(rr);
    }
}
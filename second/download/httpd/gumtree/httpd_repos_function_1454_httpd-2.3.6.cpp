static void emit_tail(request_rec *r, char *readme_fname, int suppress_amble)
{
    apr_file_t *f = NULL;
    request_rec *rr = NULL;
    int suppress_post = 0;
    int suppress_sig = 0;

    /*
     * If there's a readme file, send a subrequest to look for it.  If it's
     * found and a text file, handle it -- otherwise fall through and
     * pretend there's nothing there.
     */
    if ((readme_fname != NULL)
        && (rr = ap_sub_req_lookup_uri(readme_fname, r, r->output_filters))
        && (rr->status == HTTP_OK)
        && (rr->filename != NULL)
        && rr->finfo.filetype == APR_REG) {
        /*
         * Check for the two specific cases we allow: text/html and
         * text/anything-else.  The former is allowed to be processed for
         * SSIs.
         */
        if (rr->content_type != NULL) {
            if (response_is_html(rr)) {
                ap_filter_t *f;
                for (f=rr->output_filters;
                     f->frec != ap_subreq_core_filter_handle; f = f->next);
                f->next = r->output_filters;


                if (ap_run_sub_req(rr) == OK) {
                    /* worked... */
                    suppress_sig = 1;
                    suppress_post = suppress_amble;
                }
            }
            else if (!strncasecmp("text/", rr->content_type, 5)) {
                /*
                 * If we can open the file, suppress the signature.
                 */
                if (apr_file_open(&f, rr->filename, APR_READ,
                                  APR_OS_DEFAULT, r->pool) == APR_SUCCESS) {
                    do_emit_plain(r, f);
                    apr_file_close(f);
                    suppress_sig = 1;
                }
            }
        }
    }

    if (!suppress_sig) {
        ap_rputs(ap_psignature("", r), r);
    }
    if (!suppress_post) {
        ap_rputs("</body></html>\n", r);
    }
    if (rr != NULL) {
        ap_destroy_sub_req(rr);
    }
}
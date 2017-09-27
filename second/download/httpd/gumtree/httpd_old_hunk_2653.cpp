     * we're in better shape.
     */
    if (!ctx) {
        char *token;
        const char *encoding;

        /*
         * Only work on main request, not subrequests,
         * that are not a 204 response with no content
         * and are not tagged with the no-gzip env variable
         * and not a partial response to a Range request.
         */
        if ((r->main != NULL) || (r->status == HTTP_NO_CONTENT) ||
            apr_table_get(r->subprocess_env, "no-gzip") ||
            apr_table_get(r->headers_out, "Content-Range")
           ) {
            ap_remove_output_filter(f);
            return ap_pass_brigade(f->next, bb);
        }

        /* Some browsers might have problems with content types
         * other than text/html, so set gzip-only-text/html

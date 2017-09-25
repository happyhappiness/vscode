         * was a local redirect and the requested resource failed
         * for any reason, the custom_response will still hold the
         * redirect URL. We don't really want to output this URL
         * as a text message, so first check the custom response
         * string to ensure that it is a text-string (using the
         * same test used in ap_die(), i.e. does it start with a ").
         * 
         * If it's not a text string, we've got a recursive error or 
         * an external redirect.  If it's a recursive error, ap_die passes
         * us the second error code so we can write both, and has already 
         * backed up to the original error.  If it's an external redirect, 
         * it hasn't happened yet; we may never know if it fails.
         */
        if (custom_response[0] == '\"') {
            ap_rputs(custom_response + 1, r);
            ap_finalize_request_protocol(r);
            return;
        }
    }
    {
        const char *title = status_lines[idx];
        const char *h1;

        /* Accept a status_line set by a module, but only if it begins
         * with the 3 digit status code
         */
        if (r->status_line != NULL
            && strlen(r->status_line) > 4       /* long enough */
            && apr_isdigit(r->status_line[0])

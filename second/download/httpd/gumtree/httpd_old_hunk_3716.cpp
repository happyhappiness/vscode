
        /*
         * If next != NULL then we left the while above because of
         * next->frec == ap_http_header_filter
         */
        if (next) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01579)
                          "Custom error page caused AP_FILTER_ERROR");
            type = HTTP_INTERNAL_SERVER_ERROR;
        }
        else {
            return;
        }
    }

    if (type == DONE) {
        ap_finalize_request_protocol(r);
        return;
    }

    /*
     * The following takes care of Apache redirects to custom response URLs
     * Note that if we are already dealing with the response to some other
     * error condition, we just report on the original error, and give up on
     * any attempt to handle the other thing "intelligently"...
     */
    if (r->status != HTTP_OK) {
        recursive_error = type;

        while (r_1st_err->prev && (r_1st_err->prev->status != HTTP_OK))
            r_1st_err = r_1st_err->prev;  /* Get back to original error */

        if (r_1st_err != r) {
            /* The recursive error was caused by an ErrorDocument specifying
             * an internal redirect to a bad URI.  ap_internal_redirect has

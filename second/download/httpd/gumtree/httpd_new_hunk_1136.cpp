    int error_index = ap_index_of_response(type);
    char *custom_response = ap_response_code_string(r, error_index);
    int recursive_error = 0;
    request_rec *r_1st_err = r;

    if (type == AP_FILTER_ERROR) {
        ap_filter_t *next;

        /*
         * Check if we still have the ap_http_header_filter in place. If
         * this is the case we should not ignore AP_FILTER_ERROR here because
         * it means that we have not sent any response at all and never
         * will. This is bad. Sent an internal server error instead.
         */
        next = r->output_filters;
        while (next && (next->frec != ap_http_header_filter_handle)) {
               next = next->next;
        }

        /*
         * If next != NULL then we left the while above because of
         * next->frec == ap_http_header_filter
         */
        if (next) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
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

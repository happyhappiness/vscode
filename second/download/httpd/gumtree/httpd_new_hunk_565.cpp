    r->status          = HTTP_REQUEST_TIME_OUT;  /* Until we get a request */
    r->the_request     = NULL;

    /* Get the request... */
    if (!read_request_line(r)) {
        if (r->status == HTTP_REQUEST_URI_TOO_LARGE) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                          "request failed: URI too long");
            ap_send_error_response(r, 0);
            ap_run_log_transaction(r);
            return r;
        }

        return NULL;
    }

    if (!r->assbackwards) {
        ap_get_mime_headers(r);
        if (r->status != HTTP_REQUEST_TIME_OUT) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                          "request failed: error reading the headers");
            ap_send_error_response(r, 0);
            ap_run_log_transaction(r);
            return r;
        }
    }

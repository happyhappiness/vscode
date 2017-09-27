         * hostname, either with a full URL or a Host: header. We therefore
         * need to (as per the 1.1 spec) send an error.  As a special case,
         * HTTP/1.1 mentions twice (S9, S14.23) that a request MUST contain
         * a Host: header, and the server MUST respond with 400 if it doesn't.
         */
        r->status = HTTP_BAD_REQUEST;
        ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, r, APLOGNO(00569)
                      "client sent HTTP/1.1 request without hostname "
                      "(see RFC2616 section 14.23): %s", r->uri);
    }

    /*
     * Add the HTTP_IN filter here to ensure that ap_discard_request_body

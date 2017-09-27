    /* Get the request... */
    if (!read_request_line(r, tmp_bb)) {
        if (r->status == HTTP_REQUEST_URI_TOO_LARGE
            || r->status == HTTP_BAD_REQUEST) {
            if (r->status == HTTP_REQUEST_URI_TOO_LARGE) {
                ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, r, APLOGNO(00565)
                              "request failed: client's request-line exceeds LimitRequestLine (longer than %d)",
                              r->server->limit_req_line);
            }
            else if (r->method == NULL) {
                ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, r, APLOGNO(00566)
                              "request failed: invalid characters in URI");
            }

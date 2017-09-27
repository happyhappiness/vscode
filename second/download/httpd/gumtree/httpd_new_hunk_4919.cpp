    if (APLOGrtrace5(r)) {
        ap_log_rerror(APLOG_MARK, APLOG_TRACE5, 0, r,
                      "Request received from client: %s",
                      ap_escape_logitem(r->pool, r->the_request));
    }

    r->request_time = apr_time_now();
    ll = r->the_request;
    r->method = ap_getword_white(r->pool, &ll);

    uri = ap_getword_white(r->pool, &ll);

    /* Provide quick information about the request method as soon as known */

    r->method_number = ap_method_number_of(r->method);
    if (r->method_number == M_GET && r->method[0] == 'H') {

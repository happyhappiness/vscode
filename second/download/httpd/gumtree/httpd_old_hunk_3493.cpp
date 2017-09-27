
    if (r->proto_num < 1001) {
        /* don't send interim response to HTTP/1.0 Client */
        return;
    }
    if (!ap_is_HTTP_INFO(r->status)) {
        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                      "Status is %d - not sending interim response", r->status);
        return;
    }
    if ((r->status == HTTP_CONTINUE) && !r->expecting_100) {
        /*
         * Don't send 100-Continue when there was no Expect: 100-continue

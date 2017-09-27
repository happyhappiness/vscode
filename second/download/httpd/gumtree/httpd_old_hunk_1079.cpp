        r->status = HTTP_BAD_REQUEST;
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                      "client sent HTTP/1.1 request without hostname "
                      "(see RFC2616 section 14.23): %s", r->uri);
    }

    if (r->status != HTTP_OK) {
        ap_send_error_response(r, 0);
        ap_update_child_status(conn->sbh, SERVER_BUSY_LOG, r);
        ap_run_log_transaction(r);
        return r;
    }

        else {
            r->status = HTTP_EXPECTATION_FAILED;
            ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, r,
                          "client sent an unrecognized expectation value of "
                          "Expect: %s", expect);
            ap_send_error_response(r, 0);
            ap_update_child_status(conn->sbh, SERVER_BUSY_LOG, r);
            ap_run_log_transaction(r);
            return r;
        }
    }

    ap_add_input_filter_handle(ap_http_input_filter_handle,
                               NULL, r, r->connection);

    if ((access_status = ap_run_post_read_request(r))) {
        ap_die(access_status, r);
        ap_update_child_status(conn->sbh, SERVER_BUSY_LOG, r);
        ap_run_log_transaction(r);
        return NULL;
    }

    return r;
}

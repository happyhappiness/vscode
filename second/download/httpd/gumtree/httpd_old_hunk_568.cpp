         */
        if (strcasecmp(expect, "100-continue") == 0) {
            r->expecting_100 = 1;
        }
        else {
            r->status = HTTP_EXPECTATION_FAILED;
            ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_INFO, 0, r,
                          "client sent an unrecognized expectation value of "
                          "Expect: %s", expect);
            ap_send_error_response(r, 0);
            (void) ap_discard_request_body(r);
            ap_run_log_transaction(r);
            return r;
        }
    }

    ap_add_input_filter_handle(ap_http_input_filter_handle,

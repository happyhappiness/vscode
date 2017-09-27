            ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, r,
                          "client sent an unrecognized expectation value of "
                          "Expect: %s", expect);
            ap_send_error_response(r, 0);
            ap_update_child_status(conn->sbh, SERVER_BUSY_LOG, r);
            ap_run_log_transaction(r);
            return r;
        }
    }

    return r;
}

/* if a request with a body creates a subrequest, remove original request's
 * input headers which pertain to the body which has already been read.
 * out-of-line helper function for ap_set_sub_req_protocol.

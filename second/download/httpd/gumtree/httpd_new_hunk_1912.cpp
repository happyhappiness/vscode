            ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, r,
                          "client sent an unrecognized expectation value of "
                          "Expect: %s", expect);
            ap_send_error_response(r, 0);
            ap_update_child_status(conn->sbh, SERVER_BUSY_LOG, r);
            ap_run_log_transaction(r);
            goto traceout;
        }
    }

    AP_READ_REQUEST_SUCCESS((uintptr_t)r, (char *)r->method, (char *)r->uri, (char *)r->server->defn_name, r->status);
    return r;
    traceout:
    AP_READ_REQUEST_FAILURE((uintptr_t)r);
    return r;
}

/* if a request with a body creates a subrequest, remove original request's
 * input headers which pertain to the body which has already been read.
 * out-of-line helper function for ap_set_sub_req_protocol.

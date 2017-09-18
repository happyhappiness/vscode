            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                          "client sent invalid HTTP/0.9 request: HEAD %s",
                          r->uri);
            r->header_only = 0;
            r->status = HTTP_BAD_REQUEST;
            ap_send_error_response(r, 0);
            ap_update_child_status(conn->sbh, SERVER_BUSY_LOG, r);
            ap_run_log_transaction(r);
            apr_brigade_destroy(tmp_bb);
            return r;
        }
    }


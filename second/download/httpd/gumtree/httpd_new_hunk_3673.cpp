                              r->server->limit_req_line);
            }
            else if (r->method == NULL) {
                ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, r, APLOGNO(00566)
                              "request failed: invalid characters in URI");
            }
            access_status = r->status;
            r->status = HTTP_OK;
            ap_die(access_status, r);
            ap_update_child_status(conn->sbh, SERVER_BUSY_LOG, r);
            ap_run_log_transaction(r);
            r = NULL;
            apr_brigade_destroy(tmp_bb);
            goto traceout;
        }
        else if (r->status == HTTP_REQUEST_TIME_OUT) {
            ap_update_child_status(conn->sbh, SERVER_BUSY_LOG, r);
            if (!r->connection->keepalives) {

ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                              "request failed: URI too long (longer than %d)", r->server->limit_req_line);
ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, r,
                              "request failed: client's request-line exceeds LimitRequestLine (longer than %d)",
                              r->server->limit_req_line);
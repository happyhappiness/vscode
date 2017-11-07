ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, r, APLOGNO(00565)
                              "request failed: URI too long (longer than %d)",
                              r->server->limit_req_line);
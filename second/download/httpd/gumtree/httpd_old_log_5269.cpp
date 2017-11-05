ap_log_rerror(APLOG_MARK, APLOG_DEBUG, status, r,
                  "h2_request(%d): written request %s %s, host=%s",
                  req->id, req->method, req->path, req->authority);
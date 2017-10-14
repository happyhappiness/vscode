ap_log_perror(APLOG_MARK, APLOG_DEBUG, APR_EINVAL, pool,
                      "h2_request(%d): pseudo header in trailer",
                      req->id);
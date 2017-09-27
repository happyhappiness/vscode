ap_log_perror(APLOG_MARK, APLOG_ERR, 0, pool,
                          APLOGNO(02917) 
                          "h2_request(%d): pseudo header after request start",
                          req->id);
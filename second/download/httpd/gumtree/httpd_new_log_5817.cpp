ap_log_perror(APLOG_MARK, APLOG_WARNING, 0, pool,
                          APLOGNO(02954) 
                          "h2_request(%d): ignoring unknown pseudo header %s",
                          req->id, buffer);
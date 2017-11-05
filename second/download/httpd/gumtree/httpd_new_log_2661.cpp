ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01785)
                              "uri mismatch - <%s> does not match "
                              "request-uri <%s>", resp->uri, r_uri.hostinfo);
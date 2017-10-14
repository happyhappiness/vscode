ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01786)
                          "uri mismatch - <%s> does not match "
                          "request-uri <%s>", resp->uri, resp->raw_request_uri);
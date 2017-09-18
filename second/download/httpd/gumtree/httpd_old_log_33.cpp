ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, 0, r,
                          "Digest: uri mismatch - <%s> does not match "
                          "request-uri <%s>", resp->uri, resp->raw_request_uri);
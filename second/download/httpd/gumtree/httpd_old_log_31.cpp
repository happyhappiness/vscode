ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, 0, r,
                          "Digest: invalid uri <%s> in Authorization header",
                          resp->uri);
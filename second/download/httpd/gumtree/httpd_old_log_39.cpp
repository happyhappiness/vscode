ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, 0, r,
                          "Digest: invalid qop `%s' received: %s",
                          resp->message_qop, r->uri);
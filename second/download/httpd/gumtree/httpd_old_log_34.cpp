ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, 0, r,
                      "Digest: received invalid opaque - got `%s'",
                      resp->opaque);
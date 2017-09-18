ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, 0, r,
                      "Digest: realm mismatch - got `%s' but expected `%s'",
                      resp->realm, conf->realm);
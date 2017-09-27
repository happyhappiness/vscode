ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                          "Digest: invalid nc %s received - no nonce count allowed when qop=none",
                          snc);
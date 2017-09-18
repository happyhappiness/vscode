ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_INFO, 0, r,
                          "Digest: user %s: one-time-nonce mismatch - sending "
                          "new nonce", r->user);
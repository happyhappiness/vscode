ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, 0, r,
                      "Digest: invalid nonce %s received - user attempted "
                      "time travel", resp->nonce);
ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                      "Digest: invalid nonce %s received - hash is not %s",
                      resp->nonce, hash);
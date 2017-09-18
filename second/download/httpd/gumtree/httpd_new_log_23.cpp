ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                      "Digest: invalid nonce %s received - length is not %d",
                      resp->nonce, NONCE_LEN);
ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01775)
                      "invalid nonce %s received - length is not %d",
                      resp->nonce, NONCE_LEN);
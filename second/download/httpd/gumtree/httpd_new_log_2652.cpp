ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01776)
                      "invalid nonce %s received - hash is not %s",
                      resp->nonce, hash);
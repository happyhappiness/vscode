ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01777)
                      "invalid nonce %s received - user attempted "
                      "time travel", resp->nonce);
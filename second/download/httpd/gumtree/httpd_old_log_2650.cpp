ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                      "Digest: Warning, possible replay attack: nonce-count "
                      "check failed: %lu != %lu", nc,
                      resp->client->nonce_count);
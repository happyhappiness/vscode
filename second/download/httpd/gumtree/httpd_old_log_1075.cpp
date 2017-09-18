ap_log_rerror(APLOG_MARK, APLOG_INFO, 0,r,
                          "Digest: user %s: nonce expired (%.2f seconds old "
                          "- max lifetime %.2f) - sending new nonce", 
                          r->user, ((double)dt)/APR_USEC_PER_SEC, 
                          ((double)(conf->nonce_lifetime))/APR_USEC_PER_SEC);
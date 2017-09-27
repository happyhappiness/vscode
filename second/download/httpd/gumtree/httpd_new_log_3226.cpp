ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01782)
                          "missing user, realm, nonce, uri, digest, "
                          "cnonce, or nonce_count in authorization header: %s",
                          r->uri);
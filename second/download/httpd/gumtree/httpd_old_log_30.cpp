ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, 0, r,
                          "Digest: missing user, realm, nonce, uri, digest, "
                          "cnonce, or nonce_count in authorization header: %s",
                          r->uri);
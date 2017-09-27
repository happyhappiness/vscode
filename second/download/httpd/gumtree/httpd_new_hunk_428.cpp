                    return HTTP_FORBIDDEN;
                }

                X509_free(peercert);
            }
        }
        
        /*
         * Also check that SSLCipherSuite has been enforced as expected.
         */
        if (cipher_list) {
            cipher = SSL_get_current_cipher(ssl);
            if (sk_SSL_CIPHER_find(cipher_list, cipher) < 0) {
                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                             "SSL cipher suite not renegotiated: "
                             "access to %s denied using cipher %s",
                              r->filename,
                              SSL_CIPHER_get_name(cipher));
                return HTTP_FORBIDDEN;
            }
        }
    }

    /*
     * Check SSLRequire boolean expressions
     */
    requires = dc->aRequirement;

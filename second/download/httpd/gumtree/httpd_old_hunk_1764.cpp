            !modssl_set_cipher_list(ssl, dc->szCipherSuite ?
                                         dc->szCipherSuite :
                                         sc->server->auth.cipher_suite)) {
            ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r,
                          "Unable to reconfigure (per-directory) "
                          "permitted SSL ciphers");
            ssl_log_ssl_error(APLOG_MARK, APLOG_ERR, r->server);

            if (cipher_list_old) {
                sk_SSL_CIPHER_free(cipher_list_old);
            }

            return HTTP_FORBIDDEN;

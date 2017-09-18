                cipher_list_old = sk_SSL_CIPHER_dup(cipher_list_old);
            }
        }

        /* configure new state */
        if (!modssl_set_cipher_list(ssl, dc->szCipherSuite)) {
            ssl_log(r->server, SSL_LOG_WARN|SSL_ADD_SSLERR,
                    "Unable to reconfigure (per-directory) "
                    "permitted SSL ciphers");

            if (cipher_list_old) {
                sk_SSL_CIPHER_free(cipher_list_old);
            }

            return HTTP_FORBIDDEN;

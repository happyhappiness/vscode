
            n = BIO_read(bio, buff, sizeof(buff));
            buff[n] = '\0';

            BIO_free(bio);

            ssl_log(s, SSL_LOG_TRACE, buff);
        }

        /*
         * Verify the signature on this CRL
         */
        if (X509_CRL_verify(crl, X509_get_pubkey(cert)) <= 0) {
            ssl_log(s, SSL_LOG_WARN, "Invalid signature on CRL");

            X509_STORE_CTX_set_error(ctx, X509_V_ERR_CRL_SIGNATURE_FAILURE);
            X509_OBJECT_free_contents(&obj);

            return FALSE;
        }

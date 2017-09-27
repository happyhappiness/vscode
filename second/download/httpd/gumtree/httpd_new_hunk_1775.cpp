
            n = BIO_read(bio, buff, sizeof(buff) - 1);
            buff[n] = '\0';

            BIO_free(bio);

            ap_log_error(APLOG_MARK, APLOG_TRACE1, 0, s, "%s", buff);
        }

        /*
         * Verify the signature on this CRL
         */
        pubkey = X509_get_pubkey(cert);

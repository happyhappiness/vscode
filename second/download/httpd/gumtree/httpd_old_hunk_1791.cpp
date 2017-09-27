
            if (pPrivateKey == NULL) {
                ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
                            "Init: Unable to read server private key from "
                            "file %s [Hint: Perhaps it is in a separate file? "
                            "  See SSLCertificateKeyFile]", szPath);
                ssl_log_ssl_error(APLOG_MARK, APLOG_ERR, s);
                ssl_die();
            }

            /*
             * check algorithm type of private key and make
             * sure only one private key per type is used.

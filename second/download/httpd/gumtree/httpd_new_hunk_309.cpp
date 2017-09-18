    }

    for (n = 0; n < sk_X509_NAME_num(sk); n++) {
        char name_buf[256];
        X509_NAME *name = sk_X509_NAME_value(sk, n);

        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                     "CA certificate: %s",
                     X509_NAME_oneline(name, name_buf, sizeof(name_buf)));

        /*
         * note that SSL_load_client_CA_file() checks for duplicates,
         * but since we call it multiple times when reading a directory
         * we must also check for duplicates ourselves.
         */

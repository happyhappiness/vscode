    }

    /*
     * Some information about the certificate(s)
     */

    if (modssl_X509_getBC(cert, &is_ca, &pathlen)) {
        if (is_ca) {
            ap_log_error(APLOG_MARK, APLOG_WARNING, 0, s, APLOGNO(01906)
                         "%s server certificate is a CA certificate "
                         "(BasicConstraints: CA == TRUE !?)", key_id);
        }


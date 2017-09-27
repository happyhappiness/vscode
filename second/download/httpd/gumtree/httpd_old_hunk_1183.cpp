         * Read in server certificate(s): This is the easy part
         * because this file isn't encrypted in any way.
         */
        if (sc->server->pks->cert_files[0] == NULL) {
            ap_log_error(APLOG_MARK, APLOG_ERR, 0, pServ,
                         "Server should be SSL-aware but has no certificate "
                         "configured [Hint: SSLCertificateFile]");
            ssl_die();
        }
        algoCert = SSL_ALGO_UNKNOWN;
        algoKey  = SSL_ALGO_UNKNOWN;
        for (i = 0, j = 0; i < SSL_AIDX_MAX && sc->server->pks->cert_files[i] != NULL; i++) {


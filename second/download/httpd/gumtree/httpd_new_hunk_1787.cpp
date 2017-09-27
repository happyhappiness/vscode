                     "Loading certificate & private key of SSL-aware server");

        /*
         * Read in server certificate(s): This is the easy part
         * because this file isn't encrypted in any way.
         */
        if (sc->server->pks->cert_files[0] == NULL
            && sc->server->pkcs7 == NULL) {
            ap_log_error(APLOG_MARK, APLOG_ERR, 0, pServ,
                         "Server should be SSL-aware but has no certificate "
                         "configured [Hint: SSLCertificateFile] (%s:%d)",
                         pServ->defn_name, pServ->defn_line_number);
            ssl_die();
        }

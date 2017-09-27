            ap_log_error(APLOG_MARK, APLOG_ERR, 0, pServ,
                         "Server should be SSL-aware but has no certificate "
                         "configured [Hint: SSLCertificateFile] (%s:%d)",
                         pServ->defn_name, pServ->defn_line_number);
            ssl_die();
        }
        algoCert = SSL_ALGO_UNKNOWN;
        algoKey  = SSL_ALGO_UNKNOWN;
        for (i = 0, j = 0; i < SSL_AIDX_MAX && sc->server->pks->cert_files[i] != NULL; i++) {

            apr_cpystrn(szPath, sc->server->pks->cert_files[i], sizeof(szPath));
            if ((rv = exists_and_readable(szPath, p, NULL)) != APR_SUCCESS) {
                ap_log_error(APLOG_MARK, APLOG_ERR, rv, s,
                             "Init: Can't open server certificate file %s",
                             szPath);
                ssl_die();
            }
            if ((pX509Cert = SSL_read_X509(szPath, NULL, NULL)) == NULL) {
                ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
                        "Init: Unable to read server certificate from file %s", szPath);
                ssl_log_ssl_error(APLOG_MARK, APLOG_ERR, s);
                ssl_die();
            }

            /*
             * check algorithm type of certificate and make
             * sure only one certificate per type is used.
             */
            at = ssl_util_algotypeof(pX509Cert, NULL);
            an = ssl_util_algotypestr(at);

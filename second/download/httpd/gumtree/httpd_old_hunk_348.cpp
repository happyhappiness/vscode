        sc = mySrvConfig(pServ);

        if (!sc->enabled)
            continue;

        cpVHostID = ssl_util_vhostid(p, pServ);
        ssl_log(pServ, SSL_LOG_INFO|SSL_INIT,
                "Loading certificate & private key of SSL-aware server");

        /*
         * Read in server certificate(s): This is the easy part
         * because this file isn't encrypted in any way.
         */
        if (sc->server->pks->cert_files[0] == NULL) {
            ssl_log(pServ, SSL_LOG_ERROR|SSL_INIT,
                    "Server should be SSL-aware but has no certificate configured "
                    "[Hint: SSLCertificateFile]");
            ssl_die();
        }
        algoCert = SSL_ALGO_UNKNOWN;
        algoKey  = SSL_ALGO_UNKNOWN;
        for (i = 0, j = 0; i < SSL_AIDX_MAX && sc->server->pks->cert_files[i] != NULL; i++) {

            apr_cpystrn(szPath, sc->server->pks->cert_files[i], sizeof(szPath));
            if ( exists_and_readable(szPath, p, NULL) != APR_SUCCESS ) {
                ssl_log(s, SSL_LOG_ERROR|SSL_ADD_ERRNO,
                        "Init: Can't open server certificate file %s", szPath);
                ssl_die();
            }
            if ((pX509Cert = SSL_read_X509(szPath, NULL, NULL)) == NULL) {
                ssl_log(s, SSL_LOG_ERROR|SSL_ADD_SSLERR,
                        "Init: Unable to read server certificate from file %s", szPath);
                ssl_die();
            }

            /*
             * check algorithm type of certificate and make
             * sure only one certificate per type is used.
             */
            at = ssl_util_algotypeof(pX509Cert, NULL);
            an = ssl_util_algotypestr(at);
            if (algoCert & at) {
                ssl_log(s, SSL_LOG_ERROR|SSL_ADD_SSLERR,
                        "Init: Multiple %s server certificates not allowed", an);
                ssl_die();
            }
            algoCert |= at;

            /*
             * Insert the certificate into global module configuration to let it

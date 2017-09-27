             (!sc2->server->auth.f || \
              strNE(sc1->server->auth.f, sc2->server->auth.f)))

            if (MODSSL_CFG_CA_NE(ca_cert_file, sc, hssc) ||
                MODSSL_CFG_CA_NE(ca_cert_path, sc, hssc)) {
                if (verify & SSL_VERIFY_FAIL_IF_NO_PEER_CERT) {
                    ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, r,
                         "Non-default virtual host with SSLVerify set to "
                         "'require' and VirtualHost-specific CA certificate "
                         "list is only available to clients with TLS server "
                         "name indication (SNI) support");
                    modssl_set_verify(ssl, verify_old, NULL);
                    return HTTP_FORBIDDEN;
                } else
                    /* let it pass, possibly with an "incorrect" peer cert,
                     * so make sure the SSL_CLIENT_VERIFY environment variable
                     * will indicate partial success only, later on.
                     */

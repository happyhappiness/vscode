    SSL_CTX_set_verify(ctx, verify, ssl_callback_SSLVerify);

    /*
     * Configure Client Authentication details
     */
    if (mctx->auth.ca_cert_file || mctx->auth.ca_cert_path) {
        ssl_log(s, SSL_LOG_TRACE|SSL_INIT,
                "Configuring client authentication");

        if (!SSL_CTX_load_verify_locations(ctx,
                                           mctx->auth.ca_cert_file,
                                           mctx->auth.ca_cert_path))
        {
            ssl_log(s, SSL_LOG_ERROR|SSL_ADD_SSLERR|SSL_INIT,
                    "Unable to configure verify locations "
                    "for client authentication");
            ssl_die();
        }

        ca_list = ssl_init_FindCAList(s, ptemp,
                                      mctx->auth.ca_cert_file,
                                      mctx->auth.ca_cert_path);
        if (!ca_list) {
            ssl_log(s, SSL_LOG_ERROR|SSL_INIT,
                    "Unable to determine list of available "
                    "CA certificates for client authentication");
            ssl_die();
        }

        SSL_CTX_set_client_CA_list(ctx, (STACK *)ca_list);

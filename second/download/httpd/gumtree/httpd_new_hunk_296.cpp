    SSL_CTX_set_verify(ctx, verify, ssl_callback_SSLVerify);

    /*
     * Configure Client Authentication details
     */
    if (mctx->auth.ca_cert_file || mctx->auth.ca_cert_path) {
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                     "Configuring client authentication");

        if (!SSL_CTX_load_verify_locations(ctx,
                                           mctx->auth.ca_cert_file,
                                           mctx->auth.ca_cert_path))
        {
            ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
                    "Unable to configure verify locations "
                    "for client authentication");
            ssl_log_ssl_error(APLOG_MARK, APLOG_ERR, s);
            ssl_die();
        }

        ca_list = ssl_init_FindCAList(s, ptemp,
                                      mctx->auth.ca_cert_file,
                                      mctx->auth.ca_cert_path);
        if (!ca_list) {
            ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
                    "Unable to determine list of available "
                    "CA certificates for client authentication");
            ssl_die();
        }

        SSL_CTX_set_client_CA_list(ctx, (STACK *)ca_list);

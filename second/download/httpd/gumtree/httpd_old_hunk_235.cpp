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

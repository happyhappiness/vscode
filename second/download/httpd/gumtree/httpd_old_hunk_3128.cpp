     */
    if (mctx->auth.ca_cert_file || mctx->auth.ca_cert_path) {
        ap_log_error(APLOG_MARK, APLOG_TRACE1, 0, s,
                     "Configuring client authentication");

        if (!SSL_CTX_load_verify_locations(ctx,
                         MODSSL_PCHAR_CAST mctx->auth.ca_cert_file,
                         MODSSL_PCHAR_CAST mctx->auth.ca_cert_path))
        {
            ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
                    "Unable to configure verify locations "
                    "for client authentication");
            ssl_log_ssl_error(SSLLOG_MARK, APLOG_ERR, s);
            ssl_die();
        }

        if (mctx->pks && (mctx->pks->ca_name_file || mctx->pks->ca_name_path)) {
            ca_list = ssl_init_FindCAList(s, ptemp,
                                          mctx->pks->ca_name_file,
                                          mctx->pks->ca_name_path);
        } else
            ca_list = ssl_init_FindCAList(s, ptemp,
                                          mctx->auth.ca_cert_file,
                                          mctx->auth.ca_cert_path);
        if (!ca_list) {
            ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
                    "Unable to determine list of acceptable "
                    "CA certificates for client authentication");
            ssl_die();
        }

        SSL_CTX_set_client_CA_list(ctx, ca_list);

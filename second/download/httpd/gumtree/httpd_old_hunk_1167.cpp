            ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
                    "Unable to determine list of acceptable "
                    "CA certificates for client authentication");
            ssl_die();
        }

        SSL_CTX_set_client_CA_list(ctx, (STACK *)ca_list);
    }

    /*
     * Give a warning when no CAs were configured but client authentication
     * should take place. This cannot work.
     */
    if (mctx->auth.verify_mode == SSL_CVERIFY_REQUIRE) {
        ca_list = (STACK_OF(X509_NAME) *)SSL_CTX_get_client_CA_list(ctx);

        if (sk_X509_NAME_num(ca_list) == 0) {
            ap_log_error(APLOG_MARK, APLOG_WARNING, 0, s,
                         "Init: Oops, you want to request client "
                         "authentication, but no CAs are known for "
                         "verification!?  [Hint: SSLCACertificate*]");

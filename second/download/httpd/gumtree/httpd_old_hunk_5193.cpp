                          ssl_callback_ServerNameIndication) ||
        !SSL_CTX_set_tlsext_servername_arg(mctx->ssl_ctx, mctx)) {
        ap_log_error(APLOG_MARK, APLOG_EMERG, 0, s, APLOGNO(01894)
                     "Unable to initialize TLS servername extension "
                     "callback (incompatible OpenSSL version?)");
        ssl_log_ssl_error(SSLLOG_MARK, APLOG_EMERG, s);
        ssl_die(s);
    }

#ifdef HAVE_OCSP_STAPLING
    /*
     * OCSP Stapling support, status_request extension
     */
    if ((mctx->pkp == FALSE) && (mctx->stapling_enabled == TRUE)) {
        modssl_init_stapling(s, p, ptemp, mctx);
    }
#endif

#ifdef HAVE_SRP
    /*
     * TLS-SRP support

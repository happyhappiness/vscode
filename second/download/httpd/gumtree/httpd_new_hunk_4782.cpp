
    ptr = asn1->cpData;
    if (!(cert = d2i_X509(NULL, &ptr, asn1->nData))) {
        ap_log_error(APLOG_MARK, APLOG_EMERG, 0, s, APLOGNO(02233)
                "Unable to import %s server certificate", type);
        ssl_log_ssl_error(SSLLOG_MARK, APLOG_EMERG, s);
        ssl_die(s);
    }

    if (SSL_CTX_use_certificate(mctx->ssl_ctx, cert) <= 0) {
        ap_log_error(APLOG_MARK, APLOG_EMERG, 0, s, APLOGNO(02234)
                "Unable to configure %s server certificate", type);
        ssl_log_ssl_error(SSLLOG_MARK, APLOG_EMERG, s);
        ssl_die(s);
    }

#ifdef HAVE_OCSP_STAPLING
    if ((mctx->pkp == FALSE) && (mctx->stapling_enabled == TRUE)) {
        if (!ssl_stapling_init_cert(s, mctx, cert)) {
            ap_log_error(APLOG_MARK, APLOG_ERR, 0, s, APLOGNO(02235)

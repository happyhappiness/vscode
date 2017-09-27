    X509 *cert;

    if (!(asn1 = ssl_asn1_table_get(mc->tPublicCert, id))) {
        return FALSE;
    }

    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                 "Configuring %s server certificate", type);

    ptr = asn1->cpData;
    if (!(cert = d2i_X509(NULL, &ptr, asn1->nData))) {
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
                "Unable to import %s server certificate", type);
        ssl_log_ssl_error(SSLLOG_MARK, APLOG_ERR, s);
        ssl_die();
    }

    if (SSL_CTX_use_certificate(mctx->ssl_ctx, cert) <= 0) {
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
                "Unable to configure %s server certificate", type);
        ssl_log_ssl_error(SSLLOG_MARK, APLOG_ERR, s);
        ssl_die();
    }
  
#ifdef HAVE_OCSP_STAPLING
    if ((mctx->pkp == FALSE) && (mctx->stapling_enabled == TRUE)) {
        if (!ssl_stapling_init_cert(s, mctx, cert)) {
            ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
                         "Unable to configure server certificate for stapling");
        }
    }
#endif

    mctx->pks->certs[idx] = cert;


    /* Check that all client certs have got certificates and private
     * keys. */
    for (n = 0; n < ncerts; n++) {
        X509_INFO *inf = sk_X509_INFO_value(sk, n);

        if (!inf->x509 || !inf->x_pkey || !inf->x_pkey->dec_pkey ||
            inf->enc_data) {
            sk_X509_INFO_free(sk);
            ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, s,
                         "incomplete client cert configured for SSL proxy "
                         "(missing or encrypted private key?)");
            ssl_die();
            return;
        }
        
        if (X509_check_private_key(inf->x509, inf->x_pkey->dec_pkey) != 1) {
            ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, s,
                           "proxy client certificate and "
                           "private key do not match");
            ssl_log_ssl_error(APLOG_MARK, APLOG_ERR, s);
            ssl_die();
            return;
        }
    }

    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                 "loaded %d client certs for SSL proxy",
                 ncerts);
    pkp->certs = sk;

    if (!pkp->ca_cert_file || !store) {
        return;
    }

    /* If SSLProxyMachineCertificateChainFile is configured, load all
     * the CA certs and have OpenSSL attempt to construct a full chain
     * from each configured end-entity cert up to a root.  This will
     * allow selection of the correct cert given a list of root CA
     * names in the certificate request from the server.  */
    pkp->ca_certs = (STACK_OF(X509) **) apr_pcalloc(p, ncerts * sizeof(sk));
    sctx = X509_STORE_CTX_new();

    if (!sctx) {
        ap_log_error(APLOG_MARK, APLOG_EMERG, 0, s,
                     "SSL proxy client cert initialization failed");

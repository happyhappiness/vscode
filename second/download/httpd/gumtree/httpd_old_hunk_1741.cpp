                "Oops, no RSA, DSA or ECC server private key found?!");
#else
                "Oops, no RSA or DSA server private key found?!");
#endif
        ssl_die();
    }

    /*
     * Try to read DH parameters from the (first) SSLCertificateFile
     */
    if ((mctx->pks->cert_files[0] != NULL) &&
        (dhparams = ssl_dh_GetParamFromFile(mctx->pks->cert_files[0]))) {
        SSL_CTX_set_tmp_dh(mctx->ssl_ctx, dhparams);
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                     "Custom DH parameters (%d bits) for %s loaded from %s",
                     BN_num_bits(dhparams->p), vhost_id,
                     mctx->pks->cert_files[0]);
        DH_free(dhparams);
    }

#ifndef OPENSSL_NO_EC
    /*
     * Similarly, try to read the ECDH curve name from SSLCertificateFile...
     */
    if ((mctx->pks->cert_files[0] != NULL) &&
        (ecparams = ssl_ec_GetParamFromFile(mctx->pks->cert_files[0])) &&
        (nid = EC_GROUP_get_curve_name(ecparams)) &&
        (eckey = EC_KEY_new_by_curve_name(nid))) {
        SSL_CTX_set_tmp_ecdh(mctx->ssl_ctx, eckey);
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                     "ECDH curve %s for %s specified in %s",
                     OBJ_nid2sn(nid), vhost_id, mctx->pks->cert_files[0]);
    }
    /*
     * ...otherwise, enable auto curve selection (OpenSSL 1.0.2 and later)
     * or configure NIST P-256 (required to enable ECDHE for earlier versions)
     */
    else {
#if defined(SSL_CTX_set_ecdh_auto)
        SSL_CTX_set_ecdh_auto(mctx->ssl_ctx, 1);
#else
        eckey = EC_KEY_new_by_curve_name(NID_X9_62_prime256v1);
        SSL_CTX_set_tmp_ecdh(mctx->ssl_ctx, eckey);
#endif
    }
    EC_KEY_free(eckey);
    EC_GROUP_free(ecparams);
#endif
}

#ifdef HAVE_TLS_SESSION_TICKETS
static void ssl_init_ticket_key(server_rec *s,
                                apr_pool_t *p,
                                apr_pool_t *ptemp,
                                modssl_ctx_t *mctx)
{
    apr_status_t rv;
    apr_file_t *fp;
    apr_size_t len;
    char buf[TLSEXT_TICKET_KEY_LEN];
    char *path;
    modssl_ticket_key_t *ticket_key = mctx->ticket_key;

    if (!ticket_key->file_path) {
        return;
    }

    path = ap_server_root_relative(p, ticket_key->file_path);

    rv = apr_file_open(&fp, path, APR_READ|APR_BINARY,
                       APR_OS_DEFAULT, ptemp);

    if (rv != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_EMERG, 0, s,
                     "Failed to open ticket key file %s: (%d) %pm",
                     path, rv, &rv);
        ssl_die();
    }

    rv = apr_file_read_full(fp, &buf[0], TLSEXT_TICKET_KEY_LEN, &len);

    if (rv != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_EMERG, 0, s,
                     "Failed to read %d bytes from %s: (%d) %pm",
                     TLSEXT_TICKET_KEY_LEN, path, rv, &rv);
        ssl_die();
    }

    memcpy(ticket_key->key_name, buf, 16);
    memcpy(ticket_key->hmac_secret, buf + 16, 16);
    memcpy(ticket_key->aes_key, buf + 32, 16);

    if (!SSL_CTX_set_tlsext_ticket_key_cb(mctx->ssl_ctx,
                                          ssl_callback_SessionTicket)) {
        ap_log_error(APLOG_MARK, APLOG_EMERG, 0, s,
                     "Unable to initialize TLS session ticket key callback "
                     "(incompatible OpenSSL version?)");
        ssl_log_ssl_error(APLOG_MARK, APLOG_EMERG, s);
        ssl_die();
    }

    ap_log_error(APLOG_MARK, APLOG_INFO, 0, s,
                 "TLS session ticket key for %s successfully loaded from %s",
                 (mySrvConfig(s))->vhost_id, path);
}
#endif

static void ssl_init_proxy_certs(server_rec *s,
                                 apr_pool_t *p,
                                 apr_pool_t *ptemp,
                                 modssl_ctx_t *mctx)
{
    int n, ncerts = 0;
    STACK_OF(X509_INFO) *sk;
    STACK_OF(X509) *chain;
    X509_STORE_CTX *sctx;
    X509_STORE *store = SSL_CTX_get_cert_store(mctx->ssl_ctx);
    modssl_pk_proxy_t *pkp = mctx->pkp;

    SSL_CTX_set_client_cert_cb(mctx->ssl_ctx,
                               ssl_callback_proxy_cert);

    if (!(pkp->cert_file || pkp->cert_path)) {

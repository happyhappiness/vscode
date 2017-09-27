    for (i = 0; i < SSL_AIDX_MAX; i++) {
        ssl_check_public_cert(s, ptemp, mctx->pks->certs[i], i);
    }

    have_rsa = ssl_server_import_key(s, mctx, rsa_id, SSL_AIDX_RSA);
    have_dsa = ssl_server_import_key(s, mctx, dsa_id, SSL_AIDX_DSA);
#ifdef HAVE_ECC
    have_ecc = ssl_server_import_key(s, mctx, ecc_id, SSL_AIDX_ECC);
#endif

    if (!(have_rsa || have_dsa
#ifdef HAVE_ECC
        || have_ecc
#endif
          )) {
        ap_log_error(APLOG_MARK, APLOG_EMERG, 0, s, APLOGNO(01911)
                "Oops, no " KEYTYPES " server private key found?!");
        ssl_die(s);
    }

    /*
     * Try to read DH parameters from the (first) SSLCertificateFile
     */
    if ((mctx->pks->cert_files[0] != NULL) &&
        (dhparams = ssl_dh_GetParamFromFile(mctx->pks->cert_files[0]))) {
        SSL_CTX_set_tmp_dh(mctx->ssl_ctx, dhparams);
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(02540)
                     "Custom DH parameters (%d bits) for %s loaded from %s",
                     BN_num_bits(dhparams->p), vhost_id,
                     mctx->pks->cert_files[0]);
    }

#ifdef HAVE_ECC
    /*
     * Similarly, try to read the ECDH curve name from SSLCertificateFile...
     */
    if ((mctx->pks->cert_files[0] != NULL) &&
        (ecparams = ssl_ec_GetParamFromFile(mctx->pks->cert_files[0])) &&
        (nid = EC_GROUP_get_curve_name(ecparams)) &&
        (eckey = EC_KEY_new_by_curve_name(nid))) {
        SSL_CTX_set_tmp_ecdh(mctx->ssl_ctx, eckey);
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(02541)
                     "ECDH curve %s for %s specified in %s",
                     OBJ_nid2sn(nid), vhost_id, mctx->pks->cert_files[0]);
    }
    /*
     * ...otherwise, configure NIST P-256 (required to enable ECDHE)
     */
    else {
        SSL_CTX_set_tmp_ecdh(mctx->ssl_ctx,
                             EC_KEY_new_by_curve_name(NID_X9_62_prime256v1));
    }
#endif
}

#ifdef HAVE_TLS_SESSION_TICKETS
static void ssl_init_ticket_key(server_rec *s,
                                apr_pool_t *p,
                                apr_pool_t *ptemp,

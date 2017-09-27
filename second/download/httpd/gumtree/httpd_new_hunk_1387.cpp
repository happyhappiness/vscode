static void ssl_init_server_certs(server_rec *s,
                                  apr_pool_t *p,
                                  apr_pool_t *ptemp,
                                  modssl_ctx_t *mctx)
{
    const char *rsa_id, *dsa_id;
#ifndef OPENSSL_NO_EC
    const char *ecc_id;
#endif
    const char *vhost_id = mctx->sc->vhost_id;
    int i;
    int have_rsa, have_dsa;
#ifndef OPENSSL_NO_EC
    int have_ecc;
#endif

    rsa_id = ssl_asn1_table_keyfmt(ptemp, vhost_id, SSL_AIDX_RSA);
    dsa_id = ssl_asn1_table_keyfmt(ptemp, vhost_id, SSL_AIDX_DSA);
#ifndef OPENSSL_NO_EC
    ecc_id = ssl_asn1_table_keyfmt(ptemp, vhost_id, SSL_AIDX_ECC);
#endif

    have_rsa = ssl_server_import_cert(s, mctx, rsa_id, SSL_AIDX_RSA);
    have_dsa = ssl_server_import_cert(s, mctx, dsa_id, SSL_AIDX_DSA);
#ifndef OPENSSL_NO_EC
    have_ecc = ssl_server_import_cert(s, mctx, ecc_id, SSL_AIDX_ECC);
#endif

    if (!(have_rsa || have_dsa
#ifndef OPENSSL_NO_EC
        || have_ecc
#endif
)) {
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
#ifndef OPENSSL_NO_EC
                "Oops, no RSA, DSA or ECC server certificate found "
#else
                "Oops, no RSA or DSA server certificate found "
#endif
                "for '%s:%d'?!", s->server_hostname, s->port);
        ssl_die();
    }

    for (i = 0; i < SSL_AIDX_MAX; i++) {
        ssl_check_public_cert(s, ptemp, mctx->pks->certs[i], i);
    }

    have_rsa = ssl_server_import_key(s, mctx, rsa_id, SSL_AIDX_RSA);
    have_dsa = ssl_server_import_key(s, mctx, dsa_id, SSL_AIDX_DSA);
#ifndef OPENSSL_NO_EC
    have_ecc = ssl_server_import_key(s, mctx, ecc_id, SSL_AIDX_ECC);
#endif

    if (!(have_rsa || have_dsa
#ifndef OPENSSL_NO_EC
        || have_ecc
#endif
          )) {
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
#ifndef OPENSSL_NO_EC
                "Oops, no RSA, DSA or ECC server private key found?!");
#else
                "Oops, no RSA or DSA server private key found?!");
#endif
        ssl_die();
    }
}

static void ssl_init_proxy_certs(server_rec *s,
                                 apr_pool_t *p,

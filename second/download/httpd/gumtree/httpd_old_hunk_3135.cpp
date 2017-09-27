
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

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
        ap_log_error(APLOG_MARK, APLOG_EMERG, 0, s, APLOGNO(01911)
                "Oops, no " KEYTYPES " server private key found?!");
        ssl_die(s);
    }
}

#ifdef HAVE_TLS_SESSION_TICKETS
static void ssl_init_ticket_key(server_rec *s,
                                apr_pool_t *p,
                                apr_pool_t *ptemp,

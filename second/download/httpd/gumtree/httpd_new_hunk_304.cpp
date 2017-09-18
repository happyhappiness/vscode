    dsa_id = ssl_asn1_table_keyfmt(ptemp, vhost_id, SSL_AIDX_DSA);

    have_rsa = ssl_server_import_cert(s, mctx, rsa_id, SSL_AIDX_RSA);
    have_dsa = ssl_server_import_cert(s, mctx, dsa_id, SSL_AIDX_DSA);

    if (!(have_rsa || have_dsa)) {
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
                "Oops, no RSA or DSA server certificate found?!");
        ssl_die();
    }

    for (i = 0; i < SSL_AIDX_MAX; i++) {
        ssl_check_public_cert(s, ptemp, mctx->pks->certs[i], i);
    }

    have_rsa = ssl_server_import_key(s, mctx, rsa_id, SSL_AIDX_RSA);
    have_dsa = ssl_server_import_key(s, mctx, dsa_id, SSL_AIDX_DSA);

    if (!(have_rsa || have_dsa)) {
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
                "Oops, no RSA or DSA server private key found?!");
        ssl_die();
    }
}

static void ssl_init_proxy_certs(server_rec *s,

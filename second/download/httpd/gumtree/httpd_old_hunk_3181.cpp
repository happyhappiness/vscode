}

#ifndef OPENSSL_NO_EC
EC_KEY *ssl_callback_TmpECDH(SSL *ssl, int export, int keylen)
{
    conn_rec *c = (conn_rec *)SSL_get_app_data(ssl);
    SSLModConfigRec *mc = myModConfig(c->base_server);
    int idx;
    static EC_KEY *ecdh = NULL;
    static init = 0;

    /* XXX Uses 256-bit key for now. TODO: support other sizes. */
    ap_log_cerror(APLOG_MARK, APLOG_TRACE2, 0, c,
                  "handing out temporary 256 bit ECC key");

    if (init == 0) {
        ecdh = EC_KEY_new();
        if (ecdh != NULL) {
            /* ecdh->group = EC_GROUP_new_by_nid(NID_secp160r2); */
            EC_KEY_set_group(ecdh, 
              EC_GROUP_new_by_curve_name(NID_X9_62_prime256v1));
        }
        init = 1;
    }
    
    return ecdh;
}
#endif

/*
 * This OpenSSL callback function is called when OpenSSL

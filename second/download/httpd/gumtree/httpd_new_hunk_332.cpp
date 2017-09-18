RSA *ssl_callback_TmpRSA(SSL *ssl, int export, int keylen)
{
    conn_rec *c = (conn_rec *)SSL_get_app_data(ssl);
    SSLModConfigRec *mc = myModConfig(c->base_server);
    int idx;

    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, c->base_server,
                 "handing out temporary %d bit RSA key", keylen);

    /* doesn't matter if export flag is on,
     * we won't be asked for keylen > 512 in that case.
     * if we are asked for a keylen > 1024, it is too expensive
     * to generate on the fly.
     * XXX: any reason not to generate 2048 bit keys at startup?

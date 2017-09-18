DH *ssl_callback_TmpDH(SSL *ssl, int export, int keylen)
{
    conn_rec *c = (conn_rec *)SSL_get_app_data(ssl);
    SSLModConfigRec *mc = myModConfig(c->base_server);
    int idx;

    ssl_log(c->base_server, SSL_LOG_TRACE,
            "handing out temporary %d bit DH key", keylen);

    switch (keylen) {
      case 512:
        idx = SSL_TMP_KEY_DH_512;
        break;


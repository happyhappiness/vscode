EC_KEY *ssl_callback_TmpECDH(SSL *ssl, int export, int keylen)
{
    conn_rec *c = (conn_rec *)SSL_get_app_data(ssl);
    SSLModConfigRec *mc = myModConfigFromConn(c);
    int idx;

    /* XXX Uses 256-bit key for now. TODO: support other sizes. */
    ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, c,
                  "handing out temporary 256 bit ECC key");

    switch (keylen) {
      case 256:
      default:
        idx = SSL_TMP_KEY_EC_256;
    }

    return (EC_KEY *)mc->pTmpKeys[idx];
}
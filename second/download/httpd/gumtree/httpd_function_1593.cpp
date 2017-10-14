RSA *ssl_callback_TmpRSA(SSL *ssl, int export, int keylen)
{
    conn_rec *c = (conn_rec *)SSL_get_app_data(ssl);
    SSLModConfigRec *mc = myModConfigFromConn(c);
    int idx;

    ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, c,
                  "handing out temporary %d bit RSA key", keylen);

    /* doesn't matter if export flag is on,
     * we won't be asked for keylen > 512 in that case.
     * if we are asked for a keylen > 1024, it is too expensive
     * to generate on the fly.
     * XXX: any reason not to generate 2048 bit keys at startup?
     */

    switch (keylen) {
      case 512:
        idx = SSL_TMP_KEY_RSA_512;
        break;

      case 1024:
      default:
        idx = SSL_TMP_KEY_RSA_1024;
    }

    return (RSA *)mc->pTmpKeys[idx];
}
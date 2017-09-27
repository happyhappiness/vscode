 * which we now just hand out on demand....
 */

RSA *ssl_callback_TmpRSA(SSL *ssl, int export, int keylen)
{
    conn_rec *c = (conn_rec *)SSL_get_app_data(ssl);
    SSLModConfigRec *mc = myModConfigFromConn(c);
    int idx;

    ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, c,
                  "handing out temporary %d bit RSA key", keylen);

    /* doesn't matter if export flag is on,

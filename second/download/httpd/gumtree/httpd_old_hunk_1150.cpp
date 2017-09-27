/*
 * Hand out the already generated DH parameters...
 */
DH *ssl_callback_TmpDH(SSL *ssl, int export, int keylen)
{
    conn_rec *c = (conn_rec *)SSL_get_app_data(ssl);
    SSLModConfigRec *mc = myModConfig(c->base_server);
    int idx;

    ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, c,
                  "handing out temporary %d bit DH key", keylen);

    switch (keylen) {

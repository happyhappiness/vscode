int ssl_init_ssl_connection(conn_rec *c, request_rec *r)
{
    SSLSrvConfigRec *sc;
    SSL *ssl;
    SSLConnRec *sslconn = myConnConfig(c);
    char *vhost_md5;
    modssl_ctx_t *mctx;
    server_rec *server;

    if (!sslconn) {
        sslconn = ssl_init_connection_ctx(c);
    }
    server = sslconn->server;
    sc = mySrvConfig(server);

    /*
     * Seed the Pseudo Random Number Generator (PRNG)
     */
    ssl_rand_seed(server, c->pool, SSL_RSCTX_CONNECT, "");

    mctx = sslconn->is_proxy ? sc->proxy : sc->server;

    /*
     * Create a new SSL connection with the configured server SSL context and
     * attach this to the socket. Additionally we register this attachment
     * so we can detach later.
     */
    if (!(ssl = SSL_new(mctx->ssl_ctx))) {
        ap_log_cerror(APLOG_MARK, APLOG_ERR, 0, c,
                      "Unable to create a new SSL connection from the SSL "
                      "context");
        ssl_log_ssl_error(SSLLOG_MARK, APLOG_ERR, server);

        c->aborted = 1;

        return DECLINED; /* XXX */
    }

    vhost_md5 = ap_md5_binary(c->pool, (unsigned char *)sc->vhost_id,
                              sc->vhost_id_len);

    if (!SSL_set_session_id_context(ssl, (unsigned char *)vhost_md5,
                                    APR_MD5_DIGESTSIZE*2))
    {
        ap_log_cerror(APLOG_MARK, APLOG_ERR, 0, c,
                      "Unable to set session id context to '%s'", vhost_md5);
        ssl_log_ssl_error(SSLLOG_MARK, APLOG_ERR, server);

        c->aborted = 1;

        return DECLINED; /* XXX */
    }

    SSL_set_app_data(ssl, c);
    SSL_set_app_data2(ssl, NULL); /* will be request_rec */

    sslconn->ssl = ssl;

    /*
     *  Configure callbacks for SSL connection
     */
    SSL_set_tmp_rsa_callback(ssl, ssl_callback_TmpRSA);
    SSL_set_tmp_dh_callback(ssl,  ssl_callback_TmpDH);
#ifndef OPENSSL_NO_EC
    SSL_set_tmp_ecdh_callback(ssl, ssl_callback_TmpECDH);
#endif

    SSL_set_verify_result(ssl, X509_V_OK);

    ssl_io_filter_init(c, r, ssl);

    return APR_SUCCESS;
}
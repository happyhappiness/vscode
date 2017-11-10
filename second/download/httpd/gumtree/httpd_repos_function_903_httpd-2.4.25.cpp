static int ssl_find_vhost(void *servername, conn_rec *c, server_rec *s)
{
    SSLSrvConfigRec *sc;
    SSL *ssl;
    BOOL found;
    SSLConnRec *sslcon;

    found = ssl_util_vhost_matches(servername, s);

    /* set SSL_CTX (if matched) */
    sslcon = myConnConfig(c);
    if (found && (ssl = sslcon->ssl) &&
        (sc = mySrvConfig(s))) {
        SSL_CTX *ctx = SSL_set_SSL_CTX(ssl, sc->server->ssl_ctx);
        /*
         * SSL_set_SSL_CTX() only deals with the server cert,
         * so we need to duplicate a few additional settings
         * from the ctx by hand
         */
        SSL_set_options(ssl, SSL_CTX_get_options(ctx));
        if ((SSL_get_verify_mode(ssl) == SSL_VERIFY_NONE) ||
            (SSL_num_renegotiations(ssl) == 0)) {
           /*
            * Only initialize the verification settings from the ctx
            * if they are not yet set, or if we're called when a new
            * SSL connection is set up (num_renegotiations == 0).
            * Otherwise, we would possibly reset a per-directory
            * configuration which was put into effect by ssl_hook_Access.
            */
            SSL_set_verify(ssl, SSL_CTX_get_verify_mode(ctx),
                           SSL_CTX_get_verify_callback(ctx));
        }

        /*
         * Adjust the session id context. ssl_init_ssl_connection()
         * always picks the configuration of the first vhost when
         * calling SSL_new(), but we want to tie the session to the
         * vhost we have just switched to. Again, we have to make sure
         * that we're not overwriting a session id context which was
         * possibly set in ssl_hook_Access(), before triggering
         * a renegotiation.
         */
        if (SSL_num_renegotiations(ssl) == 0) {
            unsigned char *sid_ctx =
                (unsigned char *)ap_md5_binary(c->pool,
                                               (unsigned char *)sc->vhost_id,
                                               sc->vhost_id_len);
            SSL_set_session_id_context(ssl, sid_ctx, APR_MD5_DIGESTSIZE*2);
        }

        /*
         * Save the found server into our SSLConnRec for later
         * retrieval
         */
        sslcon->server = s;
        sslcon->cipher_suite = sc->server->auth.cipher_suite;
        
        ap_update_child_status_from_server(c->sbh, SERVER_BUSY_READ, c, s);
        /*
         * There is one special filter callback, which is set
         * very early depending on the base_server's log level.
         * If this is not the first vhost we're now selecting
         * (and the first vhost doesn't use APLOG_TRACE4), then
         * we need to set that callback here.
         */
        if (APLOGtrace4(s)) {
            BIO *rbio = SSL_get_rbio(ssl),
                *wbio = SSL_get_wbio(ssl);
            BIO_set_callback(rbio, ssl_io_data_cb);
            BIO_set_callback_arg(rbio, (void *)ssl);
            if (wbio && wbio != rbio) {
                BIO_set_callback(wbio, ssl_io_data_cb);
                BIO_set_callback_arg(wbio, (void *)ssl);
            }
        }

        return 1;
    }

    return 0;
}
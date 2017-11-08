static int ssl_find_vhost(void *servername, conn_rec *c, server_rec *s)
{
    SSLSrvConfigRec *sc;
    SSL *ssl;
    BOOL found = FALSE;
    apr_array_header_t *names;
    int i;
    SSLConnRec *sslcon;

    /* check ServerName */
    if (!strcasecmp(servername, s->server_hostname)) {
        found = TRUE;
    }

    /*
     * if not matched yet, check ServerAlias entries
     * (adapted from vhost.c:matches_aliases())
     */
    if (!found) {
        names = s->names;
        if (names) {
            char **name = (char **)names->elts;
            for (i = 0; i < names->nelts; ++i) {
                if (!name[i])
                    continue;
                if (!strcasecmp(servername, name[i])) {
                    found = TRUE;
                    break;
                }
            }
        }
    }

    /* if still no match, check ServerAlias entries with wildcards */
    if (!found) {
        names = s->wild_names;
        if (names) {
            char **name = (char **)names->elts;
            for (i = 0; i < names->nelts; ++i) {
                if (!name[i])
                    continue;
                if (!ap_strcasecmp_match(servername, name[i])) {
                    found = TRUE;
                    break;
                }
            }
        }
    }

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
         * a renegotation.
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

        /*
         * There is one special filter callback, which is set
         * very early depending on the base_server's log level.
         * If this is not the first vhost we're now selecting
         * (and the first vhost doesn't use APLOG_TRACE4), then
         * we need to set that callback here.
         */
        if (APLOGtrace4(s)) {
            BIO_set_callback(SSL_get_rbio(ssl), ssl_io_data_cb);
            BIO_set_callback_arg(SSL_get_rbio(ssl), (void *)ssl);
        }

        return 1;
    }

    return 0;
}
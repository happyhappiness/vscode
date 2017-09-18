    /*
     * Create a new SSL connection with the configured server SSL context and
     * attach this to the socket. Additionally we register this attachment
     * so we can detach later.
     */
    if (!(ssl = SSL_new(mctx->ssl_ctx))) {
        ssl_log(c->base_server, SSL_LOG_ERROR|SSL_ADD_SSLERR,
                "Unable to create a new SSL connection from the SSL context");

        c->aborted = 1;

        return DECLINED; /* XXX */
    }

    vhost_md5 = ap_md5_binary(c->pool, sc->vhost_id, sc->vhost_id_len);

    if (!SSL_set_session_id_context(ssl, (unsigned char *)vhost_md5,
                                    MD5_DIGESTSIZE*2))
    {
        ssl_log(c->base_server, SSL_LOG_ERROR|SSL_ADD_SSLERR,
                "Unable to set session id context to `%s'", vhost_md5);

        c->aborted = 1;

        return DECLINED; /* XXX */
    }


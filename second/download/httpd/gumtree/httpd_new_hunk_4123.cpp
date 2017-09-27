
    /*
     * Create a new SSL connection with the configured server SSL context and
     * attach this to the socket. Additionally we register this attachment
     * so we can detach later.
     */
    if (!(sslconn->ssl = ssl = SSL_new(mctx->ssl_ctx))) {
        ap_log_cerror(APLOG_MARK, APLOG_ERR, 0, c, APLOGNO(01962)
                      "Unable to create a new SSL connection from the SSL "
                      "context");
        ssl_log_ssl_error(SSLLOG_MARK, APLOG_ERR, server);

        c->aborted = 1;

        return DECLINED; /* XXX */
    }

    rc = ssl_run_pre_handshake(c, ssl, sslconn->is_proxy ? 1 : 0);
    if (rc != OK && rc != DECLINED) {
        return rc;
    }

    vhost_md5 = ap_md5_binary(c->pool, (unsigned char *)sc->vhost_id,
                              sc->vhost_id_len);

    if (!SSL_set_session_id_context(ssl, (unsigned char *)vhost_md5,
                                    APR_MD5_DIGESTSIZE*2))
    {

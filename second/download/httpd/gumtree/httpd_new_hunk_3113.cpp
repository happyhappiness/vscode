    vhost_md5 = ap_md5_binary(c->pool, (unsigned char *)sc->vhost_id,
                              sc->vhost_id_len);

    if (!SSL_set_session_id_context(ssl, (unsigned char *)vhost_md5,
                                    APR_MD5_DIGESTSIZE*2))
    {
        ap_log_cerror(APLOG_MARK, APLOG_ERR, 0, c, APLOGNO(01963)
                      "Unable to set session id context to '%s'", vhost_md5);
        ssl_log_ssl_error(SSLLOG_MARK, APLOG_ERR, server);

        c->aborted = 1;

        return DECLINED; /* XXX */

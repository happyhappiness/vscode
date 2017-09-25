
        c->aborted = 1;

        return DECLINED; /* XXX */
    }

    vhost_md5 = ap_md5_binary(c->pool, (unsigned char *)sc->vhost_id,
                              sc->vhost_id_len);

    if (!SSL_set_session_id_context(ssl, (unsigned char *)vhost_md5,
                                    MD5_DIGESTSIZE*2))
    {
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, c->base_server,
                     "Unable to set session id context to `%s'", vhost_md5);

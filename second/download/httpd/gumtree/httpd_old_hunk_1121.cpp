
    if (!SSL_set_session_id_context(ssl, (unsigned char *)vhost_md5,
                                    APR_MD5_DIGESTSIZE*2))
    {
        ap_log_cerror(APLOG_MARK, APLOG_ERR, 0, c,
                      "Unable to set session id context to `%s'", vhost_md5);
        ssl_log_ssl_error(APLOG_MARK, APLOG_ERR, c->base_server);

        c->aborted = 1;

        return DECLINED; /* XXX */
    }


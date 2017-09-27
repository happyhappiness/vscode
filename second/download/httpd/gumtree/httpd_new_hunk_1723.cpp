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


    ssl = sslconn->ssl;

    /* Perform initial SSL handshake. */
    SSL_set_accept_state(ssl);
    SSL_do_handshake(ssl);

    if (!SSL_is_init_finished(ssl)) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(02030)
                      "TLS upgrade handshake failed");
        ssl_log_ssl_error(SSLLOG_MARK, APLOG_ERR, r->server);

        return APR_ECONNABORTED;
    }

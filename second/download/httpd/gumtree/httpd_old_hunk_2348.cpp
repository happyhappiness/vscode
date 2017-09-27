    }

    SSL_set_shutdown(ssl, shutdown_type);
    SSL_smart_shutdown(ssl);

    /* and finally log the fact that we've closed the connection */
    if (APLOG_C_IS_LEVEL(c, loglevel)) {
        ap_log_cerror(APLOG_MARK, loglevel, 0, c,
                      "Connection closed to child %ld with %s shutdown "
                      "(server %s)",
                      c->id, type, ssl_util_vhostid(c->pool, mySrvFromConn(c)));
    }

    /* deallocate the SSL connection */
    if (sslconn->client_cert) {
        X509_free(sslconn->client_cert);
        sslconn->client_cert = NULL;

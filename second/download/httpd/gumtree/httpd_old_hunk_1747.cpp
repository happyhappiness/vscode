    }

    SSL_set_shutdown(ssl, shutdown_type);
    SSL_smart_shutdown(ssl);

    /* and finally log the fact that we've closed the connection */
    if (mySrvFromConn(c)->loglevel >= APLOG_INFO) {
        ap_log_cerror(APLOG_MARK, APLOG_INFO, 0, c,
                      "Connection closed to child %ld with %s shutdown "
                      "(server %s)",
                      c->id, type, ssl_util_vhostid(c->pool, mySrvFromConn(c)));
    }

    /* deallocate the SSL connection */

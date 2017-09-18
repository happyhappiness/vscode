        break;
    }

    SSL_smart_shutdown(ssl);

    /* and finally log the fact that we've closed the connection */
    if (SSLConnLogApplies(sslconn, SSL_LOG_INFO)) {
        ssl_log(conn->base_server, SSL_LOG_INFO,
                "Connection to child %d closed with %s shutdown"
                "(server %s, client %s)",
                conn->id, type,
                ssl_util_vhostid(conn->pool, conn->base_server),
                conn->remote_ip ? conn->remote_ip : "unknown");
    }

    /* deallocate the SSL connection */
    SSL_free(ssl);
    sslconn->ssl = NULL;
    filter->pssl = NULL; /* so filters know we've been shutdown */

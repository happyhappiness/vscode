        break;
    }

    SSL_smart_shutdown(ssl);

    /* and finally log the fact that we've closed the connection */
    if (conn->base_server->loglevel >= APLOG_INFO) {
        ap_log_error(APLOG_MARK, APLOG_INFO, 0, conn->base_server,
                     "Connection to child %ld closed with %s shutdown"
                     "(server %s, client %s)",
                     conn->id, type,
                     ssl_util_vhostid(conn->pool, conn->base_server),
                     conn->remote_ip ? conn->remote_ip : "unknown");
    }

    /* deallocate the SSL connection */
    SSL_free(ssl);
    sslconn->ssl = NULL;
    filter->pssl = NULL; /* so filters know we've been shutdown */

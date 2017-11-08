static apr_status_t ssl_filter_io_shutdown(ssl_filter_ctx_t *filter_ctx,
                                           conn_rec *c,
                                           int abortive)
{
    SSL *ssl = filter_ctx->pssl;
    const char *type = "";
    SSLConnRec *sslconn = myConnConfig(c);
    int shutdown_type;

    if (!ssl) {
        return APR_SUCCESS;
    }

    /*
     * Now close the SSL layer of the connection. We've to take
     * the TLSv1 standard into account here:
     *
     * | 7.2.1. Closure alerts
     * |
     * | The client and the server must share knowledge that the connection is
     * | ending in order to avoid a truncation attack. Either party may
     * | initiate the exchange of closing messages.
     * |
     * | close_notify
     * |     This message notifies the recipient that the sender will not send
     * |     any more messages on this connection. The session becomes
     * |     unresumable if any connection is terminated without proper
     * |     close_notify messages with level equal to warning.
     * |
     * | Either party may initiate a close by sending a close_notify alert.
     * | Any data received after a closure alert is ignored.
     * |
     * | Each party is required to send a close_notify alert before closing
     * | the write side of the connection. It is required that the other party
     * | respond with a close_notify alert of its own and close down the
     * | connection immediately, discarding any pending writes. It is not
     * | required for the initiator of the close to wait for the responding
     * | close_notify alert before closing the read side of the connection.
     *
     * This means we've to send a close notify message, but haven't to wait
     * for the close notify of the client. Actually we cannot wait for the
     * close notify of the client because some clients (including Netscape
     * 4.x) don't send one, so we would hang.
     */

    /*
     * exchange close notify messages, but allow the user
     * to force the type of handshake via SetEnvIf directive
     */
    if (abortive) {
        shutdown_type = SSL_SENT_SHUTDOWN|SSL_RECEIVED_SHUTDOWN;
        type = "abortive";
    }
    else switch (sslconn->shutdown_type) {
      case SSL_SHUTDOWN_TYPE_UNCLEAN:
        /* perform no close notify handshake at all
           (violates the SSL/TLS standard!) */
        shutdown_type = SSL_SENT_SHUTDOWN|SSL_RECEIVED_SHUTDOWN;
        type = "unclean";
        break;
      case SSL_SHUTDOWN_TYPE_ACCURATE:
        /* send close notify and wait for clients close notify
           (standard compliant, but usually causes connection hangs) */
        shutdown_type = 0;
        type = "accurate";
        break;
      default:
        /*
         * case SSL_SHUTDOWN_TYPE_UNSET:
         * case SSL_SHUTDOWN_TYPE_STANDARD:
         */
        /* send close notify, but don't wait for clients close notify
           (standard compliant and safe, so it's the DEFAULT!) */
        shutdown_type = SSL_RECEIVED_SHUTDOWN;
        type = "standard";
        break;
    }

    SSL_set_shutdown(ssl, shutdown_type);
    SSL_smart_shutdown(ssl);

    /* and finally log the fact that we've closed the connection */
    if (c->base_server->loglevel >= APLOG_INFO) {
        ap_log_error(APLOG_MARK, APLOG_INFO, 0, c->base_server,
                     "Connection to child %ld closed with %s shutdown"
                     "(server %s, client %s)",
                     c->id, type,
                     ssl_util_vhostid(c->pool, c->base_server),
                     c->remote_ip ? c->remote_ip : "unknown");
    }

    /* deallocate the SSL connection */
    if (sslconn->client_cert) {
        X509_free(sslconn->client_cert);
        sslconn->client_cert = NULL;
    }
    SSL_free(ssl);
    sslconn->ssl = NULL;
    filter_ctx->pssl = NULL; /* so filters know we've been shutdown */

    if (abortive) {
        /* prevent any further I/O */
        c->aborted = 1;
    }

    return APR_SUCCESS;
}
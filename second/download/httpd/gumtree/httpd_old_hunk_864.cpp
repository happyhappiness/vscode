                                  I couldn't give it up because by that
                                  time I was too famous.''
                                            -- Unknown                */
#include "mod_ssl.h"

/*
 *  Close the SSL part of the socket connection
 *  (called immediately _before_ the socket is closed)
 */
/* XXX: perhaps ssl_abort() should call us or vice-versa
 * lot of the same happening in both places
 */
apr_status_t ssl_hook_CloseConnection(SSLFilterRec *filter)
{
    SSL *ssl = filter->pssl;
    const char *type = "";
    conn_rec *conn;
    SSLConnRec *sslconn;

    if (!ssl) {
        return APR_SUCCESS;
    }

    conn = (conn_rec *)SSL_get_app_data(ssl);
    sslconn = myConnConfig(conn);

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
    switch (sslconn->shutdown_type) {
      case SSL_SHUTDOWN_TYPE_UNSET:
      case SSL_SHUTDOWN_TYPE_STANDARD:
        /* send close notify, but don't wait for clients close notify
           (standard compliant and safe, so it's the DEFAULT!) */
        SSL_set_shutdown(ssl, SSL_RECEIVED_SHUTDOWN);
        type = "standard";
        break;
      case SSL_SHUTDOWN_TYPE_UNCLEAN:
        /* perform no close notify handshake at all
           (violates the SSL/TLS standard!) */
        SSL_set_shutdown(ssl, SSL_SENT_SHUTDOWN|SSL_RECEIVED_SHUTDOWN);
        type = "unclean";
        break;
      case SSL_SHUTDOWN_TYPE_ACCURATE:
        /* send close notify and wait for clients close notify
           (standard compliant, but usually causes connection hangs) */
        SSL_set_shutdown(ssl, 0);
        type = "accurate";
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

    return APR_SUCCESS;
}

/*
 *  Post Read Request Handler
 */
int ssl_hook_ReadReq(request_rec *r)
{
    SSLConnRec *sslconn = myConnConfig(r->connection);
    SSL *ssl;

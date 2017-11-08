static apr_status_t ssl_abort(SSLFilterRec *filter, conn_rec *c)
{
    SSLConnRec *sslconn = myConnConfig(c);
    /*
     * try to gracefully shutdown the connection:
     * - send an own shutdown message (be gracefully)
     * - don't wait for peer's shutdown message (deadloop)
     * - kick away the SSL stuff immediately
     * - block the socket, so Apache cannot operate any more
     */

    SSL_set_shutdown(filter->pssl, SSL_RECEIVED_SHUTDOWN);
    SSL_smart_shutdown(filter->pssl);
    SSL_free(filter->pssl);

    filter->pssl = NULL; /* so filters know we've been shutdown */
    sslconn->ssl = NULL;
    c->aborted = 1;

    return APR_EGENERAL;
}
int SSL_smart_shutdown(SSL *ssl)
{
    int i;
    int rc;
    int flush;

    /*
     * Repeat the calls, because SSL_shutdown internally dispatches through a
     * little state machine. Usually only one or two interation should be
     * needed, so we restrict the total number of restrictions in order to
     * avoid process hangs in case the client played bad with the socket
     * connection and OpenSSL cannot recognize it.
     */
    rc = 0;
    flush = !(SSL_get_shutdown(ssl) & SSL_SENT_SHUTDOWN);
    for (i = 0; i < 4 /* max 2x pending + 2x data = 4 */; i++) {
        rc = SSL_shutdown(ssl);
        if (rc >= 0 && flush && (SSL_get_shutdown(ssl) & SSL_SENT_SHUTDOWN)) {
            /* Once the close notity is sent through the output filters,
             * ensure it is flushed through the socket.
             */
            if (BIO_flush(SSL_get_wbio(ssl)) <= 0) {
                rc = -1;
                break;
            }
            flush = 0;
        }
        if (rc != 0)
            break;
    }
    return rc;
}
static SSL *
httpsCreate(const Comm::ConnectionPointer &conn, SSL_CTX *sslContext)
{
    SSL *ssl = SSL_new(sslContext);

    if (!ssl) {
        const int ssl_error = ERR_get_error();
        debugs(83, DBG_IMPORTANT, "ERROR: httpsAccept: Error allocating handle: " << ERR_error_string(ssl_error, NULL)  );
        conn->close();
        return NULL;
    }

    SSL_set_fd(ssl, conn->fd);
    fd_table[conn->fd].ssl = ssl;
    fd_table[conn->fd].read_method = &ssl_read_method;
    fd_table[conn->fd].write_method = &ssl_write_method;

    debugs(33, 5, "httpsCreate: will negotate SSL on " << conn);
    fd_note(conn->fd, "client https start");

    return ssl;
}
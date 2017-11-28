static SSL *
httpsCreate(int newfd, ConnectionDetail *details, SSL_CTX *sslContext)
{
    SSL *ssl = SSL_new(sslContext);

    if (!ssl) {
        const int ssl_error = ERR_get_error();
        debugs(83, 1, "httpsAccept: Error allocating handle: " << ERR_error_string(ssl_error, NULL)  );
        comm_close(newfd);
        return NULL;
    }

    SSL_set_fd(ssl, newfd);
    fd_table[newfd].ssl = ssl;
    fd_table[newfd].read_method = &ssl_read_method;
    fd_table[newfd].write_method = &ssl_write_method;

    debugs(33, 5, "httpsCreate: will negotate SSL on FD " << newfd);
    fd_note(newfd, "client https start");

    return ssl;
}
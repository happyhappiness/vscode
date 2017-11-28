void
ssl_shutdown_method(int fd)
{
    SSL *ssl = fd_table[fd].ssl;

    SSL_shutdown(ssl);
}
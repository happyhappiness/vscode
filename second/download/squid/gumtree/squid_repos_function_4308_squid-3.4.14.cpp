int
ssl_write_method(int fd, const char *buf, int len)
{
    SSL *ssl = fd_table[fd].ssl;
    int i;

    if (!SSL_is_init_finished(ssl)) {
        errno = ENOTCONN;
        return -1;
    }

    i = SSL_write(ssl, buf, len);

    return i;
}
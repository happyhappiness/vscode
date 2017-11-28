int
ssl_read_method(int fd, char *buf, int len)
{
    SSL *ssl = fd_table[fd].ssl;
    int i;

#if DONT_DO_THIS

    if (!SSL_is_init_finished(ssl)) {
        errno = ENOTCONN;
        return -1;
    }

#endif

    i = SSL_read(ssl, buf, len);

    if (i > 0 && SSL_pending(ssl) > 0) {
        debugs(83, 2, "SSL FD " << fd << " is pending");
        fd_table[fd].flags.read_pending = true;
    } else
        fd_table[fd].flags.read_pending = false;

    return i;
}
static bool
Squid_SSL_accept(ConnStateData *conn, PF *callback)
{
    int fd = conn->clientConnection->fd;
    SSL *ssl = fd_table[fd].ssl;
    int ret;

    errno = 0;
    if ((ret = SSL_accept(ssl)) <= 0) {
        int xerrno = errno;
        int ssl_error = SSL_get_error(ssl, ret);

        switch (ssl_error) {

        case SSL_ERROR_WANT_READ:
            Comm::SetSelect(fd, COMM_SELECT_READ, callback, conn, 0);
            return false;

        case SSL_ERROR_WANT_WRITE:
            Comm::SetSelect(fd, COMM_SELECT_WRITE, callback, conn, 0);
            return false;

        case SSL_ERROR_SYSCALL:
            if (ret == 0) {
                debugs(83, 2, "Error negotiating SSL connection on FD " << fd << ": Aborted by client: " << ssl_error);
            } else {
                debugs(83, (xerrno == ECONNRESET) ? 1 : 2, "Error negotiating SSL connection on FD " << fd << ": " <<
                       (xerrno == 0 ? ERR_error_string(ssl_error, NULL) : xstrerr(xerrno)));
            }
            conn->clientConnection->close();
            return false;

        case SSL_ERROR_ZERO_RETURN:
            debugs(83, DBG_IMPORTANT, "Error negotiating SSL connection on FD " << fd << ": Closed by client");
            conn->clientConnection->close();
            return false;

        default:
            debugs(83, DBG_IMPORTANT, "Error negotiating SSL connection on FD " <<
                   fd << ": " << ERR_error_string(ERR_get_error(), NULL) <<
                   " (" << ssl_error << "/" << ret << ")");
            conn->clientConnection->close();
            return false;
        }

        /* NOTREACHED */
    }
    return true;
}
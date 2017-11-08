apr_status_t apr_wait_for_io_or_timeout(apr_file_t *f, apr_socket_t *s,
                                        int for_read)
{
    struct pollfd pfd;
    int rc, timeout;

    timeout    = f        ? f->timeout / 1000 : s->timeout / 1000;
    pfd.fd     = f        ? f->filedes        : s->socketdes;
    pfd.events = for_read ? POLLIN            : POLLOUT;

    do {
        rc = poll(&pfd, 1, timeout);
    } while (rc == -1 && errno == EINTR);
    if (rc == 0) {
        return APR_TIMEUP;
    }
    else if (rc > 0) {
        return APR_SUCCESS;
    }
    else {
        return errno;
    }
}
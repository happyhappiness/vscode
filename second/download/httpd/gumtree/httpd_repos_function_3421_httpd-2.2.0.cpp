apr_status_t apr_socket_sendto(apr_socket_t *sock, apr_sockaddr_t *where,
                               apr_int32_t flags, const char *buf,
                               apr_size_t *len)
{
    apr_ssize_t rv;

    do {
        rv = sendto(sock->socketdes, buf, (*len), flags, 
                    (const struct sockaddr*)&where->sa, 
                    where->salen);
    } while (rv == -1 && errno == EINTR);

    while ((rv == -1) && (errno == EAGAIN || errno == EWOULDBLOCK)
                      && (sock->timeout > 0)) {
        apr_status_t arv = apr_wait_for_io_or_timeout(NULL, sock, 0);
        if (arv != APR_SUCCESS) {
            *len = 0;
            return arv;
        } else {
            do {
                rv = sendto(sock->socketdes, buf, (*len), flags,
                            (const struct sockaddr*)&where->sa,
                            where->salen);
            } while (rv == -1 && errno == EINTR);
        }
    }
    if (rv == -1) {
        *len = 0;
        return errno;
    }
    *len = rv;
    return APR_SUCCESS;
}
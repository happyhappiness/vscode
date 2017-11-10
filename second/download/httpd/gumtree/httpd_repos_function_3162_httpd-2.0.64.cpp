apr_status_t apr_socket_recvfrom(apr_sockaddr_t *from, apr_socket_t *sock,
                                 apr_int32_t flags, char *buf, 
                                 apr_size_t *len)
{
    apr_ssize_t rv;

    do {
        rv = recvfrom(sock->socketdes, buf, (*len), flags, 
                      (struct sockaddr*)&from->sa, &from->salen);
    } while (rv == -1 && errno == EINTR);

    while (rv == -1 && (errno == EAGAIN || errno == EWOULDBLOCK) &&
        apr_is_option_set(sock->netmask, APR_SO_TIMEOUT)) {
        apr_status_t arv = apr_wait_for_io_or_timeout(NULL, sock, 1);
        if (arv != APR_SUCCESS) {
            *len = 0;
            return arv;
        } else {
            do {
                rv = recvfrom(sock->socketdes, buf, (*len), flags,
                              (struct sockaddr*)&from->sa, &from->salen);
            } while (rv == -1 && errno == EINTR);
        }
    }
    if (rv == -1) {
        (*len) = 0;
        return errno;
    }

    (*len) = rv;
    if (rv == 0 && sock->type == SOCK_STREAM) {
        return APR_EOF;
    }

    return APR_SUCCESS;
}
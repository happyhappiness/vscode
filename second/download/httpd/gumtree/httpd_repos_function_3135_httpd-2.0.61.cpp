apr_status_t apr_socket_sendv(apr_socket_t * sock, const struct iovec *vec,
                              apr_int32_t nvec, apr_size_t *len)
{
    apr_ssize_t rv;
    apr_size_t requested_len = 0;
    apr_int32_t i;

    for (i = 0; i < nvec; i++) {
        requested_len += vec[i].iov_len;
    }

    if (sock->netmask & APR_INCOMPLETE_WRITE) {
        sock->netmask &= ~APR_INCOMPLETE_WRITE;
        goto do_select;
    }

    do {
        rv = writev(sock->socketdes, vec, nvec);
    } while (rv == -1 && errno == EINTR);

    while (rv == -1 && (errno == EAGAIN || errno == EWOULDBLOCK) && 
        apr_is_option_set(sock->netmask, APR_SO_TIMEOUT)) {
        apr_status_t arv;
do_select:
        arv = apr_wait_for_io_or_timeout(NULL, sock, 0);
        if (arv != APR_SUCCESS) {
            *len = 0;
            return arv;
        }
        else {
            do {
                rv = writev(sock->socketdes, vec, nvec);
            } while (rv == -1 && errno == EINTR);
        }
    }
    if (rv == -1) {
        *len = 0;
        return errno;
    }
    if (apr_is_option_set(sock->netmask, APR_SO_TIMEOUT) &&
        rv < requested_len) {
        sock->netmask |= APR_INCOMPLETE_WRITE;
    }
    (*len) = rv;
    return APR_SUCCESS;
}
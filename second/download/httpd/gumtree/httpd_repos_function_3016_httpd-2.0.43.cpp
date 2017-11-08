apr_status_t apr_send(apr_socket_t *sock, const char *buf, apr_size_t *len)
{
    apr_ssize_t rv;
    
    if (sock->netmask & APR_INCOMPLETE_WRITE) {
        sock->netmask &= ~APR_INCOMPLETE_WRITE;
        goto do_select;
    }

    do {
        rv = write(sock->socketdes, buf, (*len));
    } while (rv == -1 && errno == EINTR);

    if (rv == -1 && (errno == EAGAIN || errno == EWOULDBLOCK) 
      && sock->timeout != 0) {
        apr_status_t arv;
do_select:
        arv = apr_wait_for_io_or_timeout(NULL, sock, 0);
        if (arv != APR_SUCCESS) {
            *len = 0;
            return arv;
        }
        else {
            do {
                rv = write(sock->socketdes, buf, (*len));
            } while (rv == -1 && errno == EINTR);
        }
    }
    if (rv == -1) {
        *len = 0;
        return errno;
    }
    if (sock->timeout && rv < *len) {
	sock->netmask |= APR_INCOMPLETE_WRITE;
    }
    (*len) = rv;
    return APR_SUCCESS;
}
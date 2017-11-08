apr_status_t apr_sendv(apr_socket_t * sock, const struct iovec *vec,
                       apr_int32_t nvec, apr_size_t *len)
{
    return apr_socket_sendv(sock, vec, nvec, len);
}
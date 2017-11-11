apr_status_t apr_sendto(apr_socket_t *sock, apr_sockaddr_t *where,
                        apr_int32_t flags, const char *buf, apr_size_t *len)
{
    return apr_socket_sendto(sock, where, flags, buf, len);
}
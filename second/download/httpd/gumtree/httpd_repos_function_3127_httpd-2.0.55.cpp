apr_status_t apr_recvfrom(apr_sockaddr_t *from, apr_socket_t *sock,
                          apr_int32_t flags, char *buf, 
                          apr_size_t *len)
{
    return apr_socket_recvfrom(from, sock, flags, buf, len);
}
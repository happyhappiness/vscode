apr_status_t apr_recv(apr_socket_t *sock, char *buf, apr_size_t *len)
{
    return apr_socket_recv(sock, buf, len);
}
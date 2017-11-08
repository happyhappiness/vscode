apr_status_t apr_send(apr_socket_t *sock, const char *buf, apr_size_t *len)
{
    return apr_socket_send(sock, buf, len);
}
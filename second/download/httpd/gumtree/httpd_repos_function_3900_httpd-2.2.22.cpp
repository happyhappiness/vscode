apr_status_t apr_socket_protocol_get(apr_socket_t *sock, int *protocol)
{
    *protocol = sock->protocol;
    return APR_SUCCESS;
}
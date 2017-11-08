apr_status_t apr_accept(apr_socket_t **new, apr_socket_t *sock,
                        apr_pool_t *connection_context)
{
    return apr_socket_accept(new, sock, connection_context);
}
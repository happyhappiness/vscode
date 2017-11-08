apr_status_t apr_socket_type_get(apr_socket_t *sock, int *type)
{
    *type = sock->type;
    return APR_SUCCESS;
}